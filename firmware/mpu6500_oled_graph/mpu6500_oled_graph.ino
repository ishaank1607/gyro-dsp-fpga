#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "mpu6500.h"

const int SCREEN_W = 128;
const int SCREEN_H = 64;
const int OLED_ADDR = 0x3C;
const int BTN_PIN = 0;                      // BOOT button
const int GRAPH_TOP = 10;                   // leave a title row
const int GRAPH_H = SCREEN_H - GRAPH_TOP;

const char* NAMES[6]  = {"AccX", "AccY", "AccZ", "GyrX", "GyrY", "GyrZ"};
const float RANGES[6] = {32768, 32768, 32768, 8000, 8000, 8000};  // +/- raw counts shown

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);
MPU6500 imu;

uint8_t hist[SCREEN_W];
int sel = 0;
bool wasDown = false;

void clearHistory() {
  memset(hist, GRAPH_TOP + (GRAPH_H - 1) / 2, sizeof(hist));
}

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT_PULLUP);

  imu.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED not found");
    while (true) delay(1000);
  }
  Wire.setClock(400000);                    // faster screen updates

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  clearHistory();
}

void loop() {
  // Button cycles the plotted signal
  bool down = digitalRead(BTN_PIN) == LOW;
  if (down && !wasDown) {
    sel = (sel + 1) % 6;
    clearHistory();
  }
  wasDown = down;

  imu.readSensor();
  int16_t vals[6] = {imu.getAccelX(), imu.getAccelY(), imu.getAccelZ(),
                     imu.getGyroX(),  imu.getGyroY(),  imu.getGyroZ()};
  int16_t v = vals[sel];

  // Scroll history left, append newest sample on the right
  memmove(hist, hist + 1, SCREEN_W - 1);
  float norm = constrain((float)v / RANGES[sel], -1.0f, 1.0f);
  hist[SCREEN_W - 1] = GRAPH_TOP + (GRAPH_H - 1) * (1.0f - norm) / 2.0f;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(NAMES[sel]);
  display.print(": ");
  display.print(v);

  int mid = GRAPH_TOP + (GRAPH_H - 1) / 2;
  for (int x = 0; x < SCREEN_W; x += 4) display.drawPixel(x, mid, SSD1306_WHITE);
  for (int x = 1; x < SCREEN_W; x++) {
    display.drawLine(x - 1, hist[x - 1], x, hist[x], SSD1306_WHITE);
  }
  display.display();
}
