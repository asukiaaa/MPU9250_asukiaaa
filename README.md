# MPU9250_asukiaaa
A library to read value of MPU9250.

# Connection
For uno, nano or so on.

| Arduino | MPU9250 |
|---------|---------|
| 3.3     | VCC     |
| A4(SDA) | SDA     |
| A5(SCL) | SCL     |
| GND     | GND     |

For other boards, please check [i2c pin assign](https://www.arduino.cc/en/Reference/Wire).

# Useage
See [example](examples/GetData/GetData.ino).

# License
MIT

# References
- [HaLakeKit-Library](https://github.com/nyampass/HaLakeKit-Library)
- [Aliexpress MPU9250](https://www.aliexpress.com/wholesale?catId=0&initiative_id=AS_20170706234529&SearchText=MPU9250)
- [AK8963 datasheet](https://strawberry-linux.com/pub/AK8963.pdf)
- [jrowberg/i2cdevlib/Arduino/AK8963](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/AK8963)
- [SparkFun_MPU-9250](https://github.com/sparkfun/SparkFun_MPU-9250_Breakout_Arduino_Library/blob/master/src/MPU9250.cpp)
