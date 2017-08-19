#include <SharpDistSensor.h>

#define IR_SENSOR_PIN A0

SharpDistSensor sensor(IR_SENSOR_PIN, 5);

void setup() {
  Serial.begin(9600);
  sensor.setModel(SharpDistSensor::GP2Y0A60SZLF_5V);
}

void loop() {
  Serial.println(sensor.getDist());
}

