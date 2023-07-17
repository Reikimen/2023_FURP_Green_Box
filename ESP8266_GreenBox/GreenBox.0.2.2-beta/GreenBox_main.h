////////////////////////////////////////////////// Setup Function //////////////////////////////////////////////////
void setup_function() {
  Wire.begin();
  Serial.begin(115200);

  // Wifi connection
  WiFi_connection();
  // Hardware initialization
  lcd_init();  // hello Liang delay 2000
  LED_RGB.begin();
  LED_RGB.setBrightness(255);
  LED_RGB.setPixelColor(0, LED_RGB.Color(255, 255, 255));  //最高亮度白色，只亮第一个LED
  LED_RGB.show();                                          //刷新显示
  VEML7700.begin();                                        // Light
  SG90_WIND.attach(PIN_SG90_WIND);
  wattmeter_initialization();
  pinMode(CO2_SENSOR_DATA_PIN, INPUT);
  attachInterrupt(INTERRUPT_NUMBER, CO2_InterruptFunc, CHANGE);

  delay(2000);  // the time used to setup

  control_led_rgb();
  delay(2000);
}

////////////////////////////////////////////////// Loop Function //////////////////////////////////////////////////
void loop_function() {
  // count + 1
  count_sht30 = count_sht30 + 1;
  count_water = count_water + 1;
  count_light = count_light + 1;
  count_CO2 = count_CO2 + 1;
  count_wattmeter = count_wattmeter + 1;
  count_wind = count_wind + 1;
  count_led = count_led + 1;
  count_lcd = count_lcd + 1;

  if (count_sht30 >= 2) {  // 1000ms 监测一次
    count_sht30 = 0;
    measure_sht30();
  }

  if (count_water >= 10) {  // 5000ms 监测一次
    count_water = 0;
    measure_water();
  }

  if (count_light >= 2) {  // 1000ms 监测一次
    count_light = 0;
    measure_VEML7700();
  }
  if (count_CO2 >= 2) {  // 1000ms 监测一次
    count_CO2 = 0;
    measure_CO2();
  }
  if (count_wattmeter >= 2) {  // 1000ms 监测一次
    count_wattmeter = 0;
    measure_wattmeter();
  }
  if (count_wind >= 12) {  // 6000ms = 10s 更改一次
    count_wind = 0;
    control_wind();
  }
  if (count_led >= 10) {  // 5000ms 更改一次
    count_led = 0;
    control_led_rgb();
  }

  if (count_lcd == 5) {  // 根据显示的需求可以调整
    lcd_display_Temp_Humidity();
  }
  if (count_lcd == 10) {
    lcd_display_CO2_Light();
  }
  if (count_lcd >= 15) {
    count_lcd = 0;
    lcd_display_water();
  }

  delay(500);  // 500 milliseconds as a unit of time measurement
}