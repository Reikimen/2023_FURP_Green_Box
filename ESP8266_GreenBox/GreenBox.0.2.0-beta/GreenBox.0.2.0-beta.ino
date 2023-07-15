#include "GreenBox_Define.h"
#include "GreenBox_Function.h"

void setup() {
  // put your setup code here, to run once:
  // ESP8266 initialization
  Wire.begin(); // init the I2C, if a problem is faced hear, use Wire.begin(SDA_PIN, SCL_PIN); 
  Serial.begin(115200);
  // Wifi connection
  WiFi_connection();
  
  // Hardware initialization
  lcd_init(); // hello Liang delay 2000
  VEML7700.begin(); // Light
  SG90_WIND.attach(PIN_SG90_WIND);
  LED_RGB.begin();
  LED_RGB.setBrightness(255);
  LED_RGB.setPixelColor(0,LED_RGB.Color(255, 255, 255)); //最高亮度白色，只亮第一个LED
  LED_RGB.show(); //刷新显示
  wattmeter_initialization();
  pinMode(CO2_SENSOR_DATA_PIN, INPUT);
  attachInterrupt(INTERRUPT_NUMBER, CO2_InterruptFunc, CHANGE);

  delay(2000); // the time used to setup
}

void loop() {
  // put your main code here, to run repeatedly:
  // get_time_from_internet();
  measure_sht30();
  measure_water();
  measure_VEML7700();
  measure_CO2();
  measure_wattmeter();
  control_wind();
  control_led_rgb();
  lcd_display();
}
