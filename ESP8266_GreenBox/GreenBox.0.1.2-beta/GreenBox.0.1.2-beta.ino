#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DFRobot_VEML7700.h>
#include <Servo.h>
#include "GreenBox_Define.h"
#include "GreenBox_Function.h"

void setup() {
  // put your setup code here, to run once:
  // ESP8266 initialization
  Wire.begin(); // init the I2C, if a problem is faced hear, use Wire.begin(SDA_PIN, SCL_PIN); 
  Serial.begin(115200);

  // hardware initialization
  lcd_init();
  VEML7700.begin();
  SG90_WIND.attach(PIN_SG90_WIND);

  delay(100); // the time used to setup
}

void loop() {
  // put your main code here, to run repeatedly:
  measure_sht30(); 
  measure_water();
  measure_VEML7700();
  control_wind();
  lcd_display();
}
