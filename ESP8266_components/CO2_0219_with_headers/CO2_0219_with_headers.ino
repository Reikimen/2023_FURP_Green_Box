#include "CO2.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("beginning...");
  pinMode(CO2_SENSOR_DATA_PIN, INPUT);
  attachInterrupt(INTERRUPT_NUMBER, CO2_InterruptFunc, CHANGE);
}

void loop() {
  measure_CO2();
  delay(1000);
}