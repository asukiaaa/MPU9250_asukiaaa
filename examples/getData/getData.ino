#include <MPU9250_asukiaaa.h>

MPU9250 mySensor;

void setup() {
  Serial.begin(115200);
  mySensor.begin();
}

void loop() {
  mySensor.accelUpdate();
  Serial.println("print xyz and comp");
  Serial.println(mySensor.accelX());
  Serial.println(mySensor.accelY());
  Serial.println(mySensor.accelZ());
  Serial.println(mySensor.accelSqrt());

  delay(100);
}
