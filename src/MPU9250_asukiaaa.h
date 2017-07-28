#ifndef MPU9250_ASUKIAAA
#define MPU9250_ASUKIAAA
#include <Arduino.h>
#include <Wire.h>

#define MPU9250_ADDRESS_AD0_LOW  0x68
#define MPU9250_ADDRESS_AD0_HIGH 0x69
#define MAG_ADDRESS              0x0C

#define GYRO_FULL_SCALE_250_DPS  0x00
#define GYRO_FULL_SCALE_500_DPS  0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G       0x00
#define ACC_FULL_SCALE_4_G       0x08
#define ACC_FULL_SCALE_8_G       0x10
#define ACC_FULL_SCALE_16_G      0x18

class MPU9250 {
  public:
  MPU9250(uint8_t address = (uint8_t) MPU9250_ADDRESS_AD0_LOW);
  void begin();
  void beginMagnetometer();
  void accelUpdate();
  float accelX();
  float accelY();
  float accelZ();
  float accelSqrt();

  private:
  uint8_t address;
  uint8_t accelBuf[14];
  float accelGet(uint8_t highIndex, uint8_t lowIndex);
};

#endif
