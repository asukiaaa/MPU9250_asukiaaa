#include <MPU9250_asukiaaa.h>

MPU9250 mySensor;

void setup() {
  while(!Serial);
  Serial.begin(115200);
  mySensor.begin();
  mySensor.beginMagnetometer();

  // you can set your own offset for mag values
  // mySensor.magXOffset = -50;
  // mySensor.magYOffset = -55;
  // mySensor.magZOffset = -10;
}

void loop() {
  mySensor.accelUpdate();
  Serial.println("print accel values");
  Serial.println("accelX: " + String(mySensor.accelX()));
  Serial.println("accelY: " + String(mySensor.accelY()));
  Serial.println("accelZ: " + String(mySensor.accelZ()));
  Serial.println("accelSqrt: " + String(mySensor.accelSqrt()));

  mySensor.magUpdate();
  Serial.println("print mag values");
  Serial.println("magX: " + String(mySensor.magX()));
  Serial.println("maxY: " + String(mySensor.magY()));
  Serial.println("magZ: " + String(mySensor.magZ()));

  Serial.println("at " + String(millis()) + "ms");
  delay(500);
}
