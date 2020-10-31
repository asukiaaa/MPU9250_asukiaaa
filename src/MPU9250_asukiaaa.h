#ifndef MPU9250_ASUKIAAA_H
#define MPU9250_ASUKIAAA_H
#include <Arduino.h>
#include <Wire.h>

#define MPU9250_ADDRESS_AD0_LOW  0x68
#define MPU9250_ADDRESS_AD0_HIGH 0x69

#define ACC_FULL_SCALE_2_G       0x00
#define ACC_FULL_SCALE_4_G       0x08
#define ACC_FULL_SCALE_8_G       0x10
#define ACC_FULL_SCALE_16_G      0x18

#define GYRO_FULL_SCALE_250_DPS  0x00
#define GYRO_FULL_SCALE_500_DPS  0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define MAG_MODE_POWERDOWN        0x0
#define MAG_MODE_SINGLE           0x1
#define MAG_MODE_CONTINUOUS_8HZ   0x2
#define MAG_MODE_EXTERNAL         0x4
#define MAG_MODE_CONTINUOUS_100HZ 0x6
#define MAG_MODE_SELFTEST         0x8
#define MAG_MODE_FUSEROM          0xF

#define MPU9250_BUFF_LEN_ACCEL 6
#define MPU9250_BUFF_LEN_GYRO  6
#define MPU9250_BUFF_LEN_MAG   7

class MPU9250_asukiaaa {
  public:
  const uint8_t address;
  int16_t magXOffset, magYOffset, magZOffset;
  uint8_t accelBuff[MPU9250_BUFF_LEN_ACCEL];
  uint8_t gyroBuff[MPU9250_BUFF_LEN_GYRO];
  uint8_t magBuff[MPU9250_BUFF_LEN_MAG];

  MPU9250_asukiaaa(uint8_t address = MPU9250_ADDRESS_AD0_LOW);
  void setWire(TwoWire *wire);
  uint8_t readId(uint8_t *id);

  void beginAccel(uint8_t mode = ACC_FULL_SCALE_16_G);
  uint8_t accelUpdate();
  float accelX();
  float accelY();
  float accelZ();
  float accelSqrt();

  void beginGyro(uint8_t mode = GYRO_FULL_SCALE_2000_DPS);
  uint8_t gyroUpdate();
  float gyroX();
  float gyroY();
  float gyroZ();

  void beginMag(uint8_t mode = MAG_MODE_CONTINUOUS_8HZ);
  void magSetMode(uint8_t mode);
  uint8_t magUpdate();
  float magX();
  float magY();
  float magZ();
  float magHorizDirection();

  private:
  TwoWire* myWire;
  float accelRange;
  float gyroRange;
  uint8_t magXAdjust, magYAdjust, magZAdjust;
  void beginWireIfNull();
  float accelGet(uint8_t highIndex, uint8_t lowIndex);
  float gyroGet(uint8_t highIndex, uint8_t lowIndex);
  int16_t magGet(uint8_t highIndex, uint8_t lowIndex);
  void magEnableSlaveMode();
  void magReadAdjustValues();
  void magWakeup();
  uint8_t i2cRead(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
  uint8_t i2cWriteByte(uint8_t Address, uint8_t Register, uint8_t Data);
};

#endif
