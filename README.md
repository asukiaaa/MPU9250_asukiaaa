# MPU9250_asukiaaa
A library to read value of MPU9250.

# Installation
You can install to Arduino IDE with using library manager.

1. Select [Sketch -> Include Library -> Manage Libraries] to open library manager.
2. Search MPU9250 in library manager.
3. Select and install this project.

# Connection
For uno, nano and so on.

| Arduino | MPU9250 |
|---------|---------|
| 3.3     | VCC     |
| A4(SDA) | SDA     |
| A5(SCL) | SCL     |
| GND     | GND     |

For other boards, please check [i2c pin assign](https://www.arduino.cc/en/Reference/Wire).

# Usage

## Accelerometer
```c
#include <MPU9250_asukiaaa.h>
MPU9250 mySensor;
float aX, aY, aZ, aSqrt;

void setup() {
  Wire.begin();
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
}

void loop() {
  mySensor.accelUpdate();
  aX = mySensor.accelX();
  aY = mySensor.accelY();
  aZ = mySensor.accelZ();
  aSqrt = mySensor.accelSqrt();
  // Do what you want
}
```

## Gyrometer
```c
```c
#include <MPU9250_asukiaaa.h>
MPU9250 mySensor;
float gX, gY, gZ;

void setup() {
  Wire.begin();
  mySensor.setWire(&Wire);
  mySensor.beginGyro();
}

void loop() {
  mySensor.gyroUpdate();
  gX = mySensor.gyroX();
  gY = mySensor.gyroY();
  gZ = mySensor.gyroZ();
  // Do what you want
}
```

## Magnetometer
```c
#include <MPU9250_asukiaaa.h>
MPU9250 mySensor;
float mDirection;
uint16_t mX, mY, mZ;

void setup() {
  Wire.begin();
  mySensor.setWire(&Wire);
  mySensor.beginMag();
}

void loop() {
  Serial.begin(115200);
  mySensor.magUpdate();
  mX = mySensor.magX();
  mY = mySensor.magY();
  mZ = mySensor.magZ();
  mDirection = mySensor.magHorizDirection();
  // Do what you want
}
```

If you get values of sensor like this..

Name | Max | Min
-----|----:|----:
magX |  70 | -30
maxY | 110 |  10

I suggest to set offset like this.

```c
void setup() {
  mySensor.magXOffset = -20;
  mySensor.magYOffset = -60;
}
```

Then you can get like this.

Name | Max | Min
-----|----:|----:
magX |  50 | -50
maxY |  50 | -50

After setting offset value, you can get `magHorizDirection` as you expected.

Warning: Offset value changes by temperature or some reason. If you want to get high accuracy value, you should recheck the offset value.

## With customizable Wire
For ESP8266, ESP32 and so on.

```c
void setup() {
  Wire.begin(26, 25); //sda, scl
  mySensor.setWire(&Wire);
}
```

## Example
See [example project](https://github.com/asukiaaa/MPU9250_asukiaaa/blob/master/examples/GetData/GetData.ino).

# License
MIT

# References
- [ArduinoでMPU9250（加速度センサ、磁気センサ）を使う方法](http://asukiaaa.blogspot.jp/2017/07/arduinompu9250.html)
- [HaLakeKit-Library](https://github.com/nyampass/HaLakeKit-Library)
- [Aliexpress MPU9250](https://www.aliexpress.com/wholesale?catId=0&initiative_id=AS_20170706234529&SearchText=MPU9250)
- [AK8963 datasheet](https://strawberry-linux.com/pub/AK8963.pdf)
- [jrowberg/i2cdevlib/Arduino/AK8963](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/AK8963)
- [SparkFun_MPU-9250](https://github.com/sparkfun/SparkFun_MPU-9250_Breakout_Arduino_Library/blob/master/src/MPU9250.cpp)
- [「MPU-9250 ９軸センサモジュール (メーカー品番：MPU-9250)」を使う](https://qiita.com/boyaki_machine/items/915f7730c737f2a5cc79)
- [【PSoC】MPU-9250のデータを取得（加速度、ジャイロ編）](http://amamitokachi.com/2017/04/12/post-71/)
