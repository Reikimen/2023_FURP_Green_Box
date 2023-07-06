//////////////////////////////////////////////////// Functions ////////////////////////////////////////////////////
// Sensors + outputs
///////////////////////////////////////////////////// Sensors /////////////////////////////////////////////////////
// SHT30
void measure_sht30(){
  //发送测量命令 0x2C06
  Wire.beginTransmission(Addr_SHT30);
  Wire.write(0x2C);
  Wire.write(0x06);
  Wire.endTransmission();
  delay(100);
  //停止IIC，并且等待sht30的读数

  //请求获取6字节的数据，然后会存到8266的内存里
  Wire.requestFrom(Addr_SHT30, 6);

  //读取6字节的数据
  //这六个字节分别为：温度8位高数据，温度8位低数据，温度8位CRC校验数据
  //               湿度8位高数据，湿度8位低数据，湿度8位CRC校验数据   目前程序没有使用 CRC校验
  if (Wire.available() == 6)
  {
    sht30_data[0] = Wire.read();
    sht30_data[1] = Wire.read();
    sht30_data[2] = Wire.read();
    sht30_data[3] = Wire.read();
    sht30_data[4] = Wire.read();
    sht30_data[5] = Wire.read();
  }

  //然后计算得到的数据，要转化为摄氏度、华氏度、相对湿度
  sht30_cTemp = ((((sht30_data[0] * 256.0) + sht30_data[1]) * 175) / 65535.0) - 45;
  sht30_fTemp = (sht30_cTemp * 1.8) + 32;
  sht30_humidity = ((((sht30_data[3] * 256.0) + sht30_data[4]) * 100) / 65535.0);

  //在串口里输出得到的数据
  Serial.print("相对湿度：");
  Serial.print(sht30_humidity);
  Serial.println(" %RH");
  Serial.print("摄氏度温度：");
  Serial.print(sht30_cTemp);
  Serial.println(" C");
  Serial.print("华氏度温度：");
  Serial.print(sht30_fTemp);
  Serial.println(" F");

}

// Water sensor
void measure_water(){
  water_depth = (long)analogRead(PIN_WATER);
  water_depth=(water_depth/650)*4;
  Serial.print("The depth of water is:");
  Serial.print(water_depth);
  Serial.println("cm");
  delay(20);
}

// VEML7700_light
void measure_VEML7700(){
  VEML7700.getALSLux(VEML7700_light);
  Serial.print("Lux: ");//Read Lux and print
  Serial.print(VEML7700_light);
  Serial.println(" lx");
  delay(20);
}

/////////////////////////////////////////////////////// Outputs ///////////////////////////////////////////////////////
// SG90_WIND
void control_wind(){
  SG90_WIND.write(wind_force);
}

// LED
void control_led_rgb(){
  LED_RGB.setBrightness(LED_RGB_Brightness);
  for (LED_kapa = 0; LED_kapa < 15; LED_kapa = LED_kapa + 1){
    LED_RGB.setPixelColor(LED_kapa,LED_RGB.Color(LED_R, LED_G, LED_B)); //红色
    LED_RGB.show(); //刷新显示
  }
}

// LCD1602
void lcd_init(){
  LCD1602.init();
  LCD1602.backlight();
  LCD1602.print("Hello, Liang!");
  delay(2000);
  LCD1602.clear();
}

void lcd_display(){

  // sht30, 需要后续调整具体LCD输出位置
  LCD1602.clear();
  LCD1602.setCursor(0, 0);//光标移动到第1行的第1个字符开始显示
  LCD1602.print("Temp: ");
  LCD1602.setCursor(6, 0);//光标移动到第1行的第7个字符开始显示
  LCD1602.print(sht30_cTemp);
  LCD1602.setCursor(11, 0);//光标移动到第1行的第12个字符开始显示
  LCD1602.print(" C");

  LCD1602.setCursor(0, 1);//光标移动到第2行的第1个字符
  LCD1602.print("RH:");
  LCD1602.setCursor(6, 1);//光标移动到第2行的第7个字符开始显示
  LCD1602.print(sht30_humidity);
  LCD1602.setCursor(11, 1);//光标移动到第1行的第12个字符开始显示
  LCD1602.print(" RH%");
  delay(3000);

  // CO2 & light
  LCD1602.clear();
  LCD1602.setCursor(0, 0);//光标移动到第1行的第1个字符开始显示
  LCD1602.print("CO2: ");
  LCD1602.setCursor(6, 0);//光标移动到第1行的第7个字符开始显示
  LCD1602.print("");
  LCD1602.setCursor(11, 0);//光标移动到第1行的第12个字符开始显示
  LCD1602.print(" ?");

  LCD1602.setCursor(0, 1);//光标移动到第2行的第1个字符
  LCD1602.print("Light:");
  LCD1602.setCursor(6, 1);//光标移动到第2行的第7个字符开始显示
  LCD1602.print(VEML7700_light);
  LCD1602.setCursor(11, 1);//光标移动到第1行的第12个字符开始显示
  LCD1602.print(" lx");
  delay(3000);

  // water depth 
  LCD1602.clear();
  LCD1602.setCursor(0, 0);//光标移动到第1行的第1个字符开始显示
  LCD1602.print("Depth: ");
  LCD1602.setCursor(6, 0);//光标移动到第1行的第7个字符开始显示
  LCD1602.print(water_depth);
  LCD1602.setCursor(11, 0);//光标移动到第1行的第12个字符开始显示
  LCD1602.print(" cm");
  delay(1500);
}
