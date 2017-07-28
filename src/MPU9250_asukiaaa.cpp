#include "MPU9250_asukiaaa.h"

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  Wire.requestFrom(Address, Nbytes);
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}

void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data) {
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

MPU9250::MPU9250(uint8_t _address) {
  address = _address;
}

void MPU9250::begin() {
  Wire.begin();
  delay(40);

  I2CwriteByte(address, 27, GYRO_FULL_SCALE_2000_DPS);
  I2CwriteByte(address, 28, ACC_FULL_SCALE_16_G);
  I2CwriteByte(MAG_ADDRESS, 0x0A, 1 << 4 || 0x02);
  delay(10);
}

void MPU9250::beginMagnetometer() {
  I2CwriteByte(address, 0x37, 0x02);
}

void MPU9250::accelUpdate() {
  I2Cread(address, 0x3B, 14, accelBuf);
}

float MPU9250::accelGet(uint8_t highIndex, uint8_t lowIndex) {
  int16_t v = -(accelBuf[highIndex]<<8 | accelBuf[lowIndex]);
  return ((float)v) * 16.0/32768.0;
}

float MPU9250::accelX() {
  return accelGet(0, 1);
}

float MPU9250::accelY() {
  return accelGet(2, 3);
}

float MPU9250::accelZ() {
  return accelGet(4, 5);
}

float MPU9250::accelSqrt() {
  return sqrt(pow(accelGet(0, 1), 2) +
              pow(accelGet(2, 3), 2) +
              pow(accelGet(4, 5), 2));
}
