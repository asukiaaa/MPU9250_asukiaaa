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

void MPU9250::begin() {
  Wire.begin();
  delay(40);

  I2CwriteByte(address, 27, GYRO_FULL_SCALE_2000_DPS);
  I2CwriteByte(address, 28, ACC_FULL_SCALE_16_G);
  delay(10);
}

void MPU9250::beginMagnetometer(uint8_t mode) {
  Wire.begin();
  delay(10);

  // read adjust values
  I2CwriteByte(address, 0x37, 0x02);
  delay(10);
  magSetMode(0x00);
  magSetMode(AK8963_MODE_FUSEROM);
  uint8_t buff[3];
  I2Cread(MAG_ADDRESS, AK8963_RA_ASAX, 3, buff);
  magXAdjust = buff[0];
  magYAdjust = buff[1];
  magZAdjust = buff[2];
  Serial.println(magXAdjust);
  Serial.println(magYAdjust);
  Serial.println(magZAdjust);

  magSetMode(0x00);
  magSetMode(mode);
}

void MPU9250::magSetMode(uint8_t mode) {
  I2CwriteByte(MAG_ADDRESS, AK8963_RA_CNTL1, mode);
  delay(10);
}

void MPU9250::magUpdate() {
  I2Cread(MAG_ADDRESS, AK8963_RA_HXL, 7, magBuf);
}

int16_t MPU9250::magGet(uint8_t highIndex, uint8_t lowIndex) {
  return (((int16_t)magBuf[highIndex]) << 8) | magBuf[lowIndex];
}

uint16_t adjustMagValue(int16_t value, uint8_t adjust) {
  return (value * ((((adjust - 128) * 0.5) / 128) + 1));
}

int16_t MPU9250::magX() {
  return adjustMagValue(magGet(1, 0), magXAdjust) + magXOffset;
}

int16_t MPU9250::magY() {
  return adjustMagValue(magGet(3, 2), magYAdjust) + magYOffset;
}

int16_t MPU9250::magZ() {
  return adjustMagValue(magGet(5, 4), magZAdjust) + magZOffset;
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
