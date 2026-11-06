#include "mpu6500.h"

MPU6500::MPU6500(uint8_t address) {
  _address = address;
}

void MPU6500::begin() {
  Wire.begin();
  Wire.beginTransmission(_address);
  Wire.write(PWR_MGMT_1);
  Wire.write(0);
  Wire.endTransmission(true);
}

void MPU6500::readSensor() {
  Wire.beginTransmission(_address);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(_address, (uint8_t)6, (uint8_t) true);

  ax = (Wire.read() << 8 | Wire.read());
  ay = (Wire.read() << 8 | Wire.read());
  az = (Wire.read() << 8 | Wire.read());

  Wire.beginTransmission(_address);
  Wire.write(GYRO_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(_address, (uint8_t)6, (uint8_t) true);

  gx = (Wire.read() << 8 | Wire.read());
  gy = (Wire.read() << 8 | Wire.read());
  gz = (Wire.read() << 8 | Wire.read());
}