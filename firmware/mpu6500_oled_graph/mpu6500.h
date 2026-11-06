#ifndef MPU6500_H
#define MPU6500_H

#include <Arduino.h>
#include <Wire.h>

class MPU6500 {
public:
  MPU6500(uint8_t address = 0x68);

  void begin();
  void readSensor();

  int16_t getAccelX() const {
    return ax;
  }
  int16_t getAccelY() const {
    return ay;
  }
  int16_t getAccelZ() const {
    return az;
  }

  int16_t getGyroX() const {
    return gx;
  }
  int16_t getGyroY() const {
    return gy;
  }
  int16_t getGyroZ() const {
    return gz;
  }

private:
  uint8_t _address;
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  static const uint8_t PWR_MGMT_1 = 0x6B;
  static const uint8_t ACCEL_XOUT_H = 0x3B;
  static const uint8_t GYRO_XOUT_H = 0x43;
};
#endif