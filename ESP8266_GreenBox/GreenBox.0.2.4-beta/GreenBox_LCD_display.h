  ////////////////////////////////////////////////// LCD display //////////////////////////////////////////////////
void lcd_init() {
  LCD1602.init();
  LCD1602.backlight();
  LCD1602.print("Hello, Liang!");
  delay(2000);
  LCD1602.clear();
}

void lcd_display_IPaddress(){
  LCD1602.clear();
  LCD1602.setCursor(0, 0);  //光标移动到第1行的第1个字符开始显示
  LCD1602.print(WiFi.localIP());
}

void lcd_display_WiFi_connection_failed() {
  // sht30, 需要后续调整具体LCD输出位置
  LCD1602.clear();
  LCD1602.setCursor(0, 0);  //光标移动到第1行的第1个字符开始显示
  LCD1602.print("WiFi failed");
}

void lcd_display_Temp_Humidity() {

  // sht30, 需要后续调整具体LCD输出位置
  LCD1602.clear();
  LCD1602.setCursor(0, 0);  //光标移动到第1行的第1个字符开始显示
  LCD1602.print("Temp: ");
  LCD1602.setCursor(6, 0);  //光标移动到第1行的第7个字符开始显示
  LCD1602.print(sht30_cTemp);
  LCD1602.setCursor(11, 0);  //光标移动到第1行的第12个字符开始显示
  LCD1602.print(" C");

  LCD1602.setCursor(0, 1);  //光标移动到第2行的第1个字符
  LCD1602.print("RH:");
  LCD1602.setCursor(6, 1);  //光标移动到第2行的第7个字符开始显示
  LCD1602.print(sht30_humidity);
  LCD1602.setCursor(11, 1);  //光标移动到第1行的第12个字符开始显示
  LCD1602.print(" RH%");
}

void lcd_display_CO2_Light() {
  // CO2 & light
  LCD1602.clear();
  LCD1602.setCursor(0, 0);  //光标移动到第1行的第1个字符开始显示
  LCD1602.print("CO2: ");
  LCD1602.setCursor(6, 0);  //光标移动到第1行的第7个字符开始显示
  LCD1602.print(CO2_concentration);
  LCD1602.setCursor(11, 0);  //光标移动到第1行的第12个字符开始显示
  LCD1602.print(" ppm");

  LCD1602.setCursor(0, 1);  //光标移动到第2行的第1个字符
  LCD1602.print("Light:");
  LCD1602.setCursor(6, 1);  //光标移动到第2行的第7个字符开始显示
  LCD1602.print(VEML7700_light);
  LCD1602.setCursor(11, 1);  //光标移动到第2行的第12个字符开始显示
  LCD1602.print(" lx");
}

void lcd_display_Light_radiation() {
  //light_radiation 光量子传感器
  LCD1602.clear();
  LCD1602.setCursor(0, 0);  //光标移动到第2行的第1个字符
  LCD1602.print("Light:");
  LCD1602.setCursor(6, 0);  //光标移动到第2行的第7个字符开始显示
  LCD1602.print(light_radiation);
  LCD1602.setCursor(11, 0);  //光标移动到第2行的第12个字符开始显示
  LCD1602.print(" umol");
}

void lcd_display_water() {
  // water depth
  LCD1602.clear();
  LCD1602.setCursor(0, 0);  //光标移动到第1行的第1个字符开始显示
  LCD1602.print("Depth: ");
  LCD1602.setCursor(6, 0);  //光标移动到第1行的第7个字符开始显示
  LCD1602.print(water_depth);
  LCD1602.setCursor(11, 0);  //光标移动到第1行的第12个字符开始显示
  LCD1602.print(" cm");
}

void lcd_display_wattmeter(int lcd_kapa) {
  LCD1602.clear();

  switch (lcd_kapa){
    case 10: { // fan 电压，电源电压
      LCD1602.setCursor(0, 0);  //光标移动到第1行的第1个字符开始显示
      LCD1602.print("Bus: ");
      LCD1602.setCursor(6, 0);  //光标移动到第1行的第10个字符开始显示
      LCD1602.print(BusVoltage_fan);
      LCD1602.setCursor(9, 0);  //光标移动到第1行的第12个字符开始显示
      LCD1602.print(" V");

      LCD1602.setCursor(0, 1);  //光标移动到第2行的第1个字符
      LCD1602.print("Shunt:");
      LCD1602.setCursor(9, 1);  //光标移动到第2行的第8个字符开始显示
      LCD1602.print(ShuntVoltage_fan);
      LCD1602.setCursor(12, 1);  //光标移动到第2行的第12个字符开始显示
      LCD1602.print(" mV");

      break;
    }
    case 11: { // fan 电流，功率
      LCD1602.setCursor(0, 0);  //光标移动到第1行的第1个字符开始显示
      LCD1602.print("Current: ");
      LCD1602.setCursor(9, 0);  //光标移动到第1行的第10个字符开始显示
      LCD1602.print(current_fan);
      LCD1602.setCursor(12, 0);  //光标移动到第1行的第12个字符开始显示
      LCD1602.print(" mA");

      LCD1602.setCursor(0, 1);  //光标移动到第2行的第1个字符
      LCD1602.print("Power:");
      LCD1602.setCursor(7, 1);  //光标移动到第2行的第8个字符开始显示
      LCD1602.print(power_fan);
      LCD1602.setCursor(11, 1);  //光标移动到第2行的第12个字符开始显示
      LCD1602.print(" mW");

      break;
    }

    case 20: { // RGB_LED 电压，电源电压
      LCD1602.setCursor(0, 0);  //光标移动到第1行的第1个字符开始显示
      LCD1602.print("Bus: ");
      LCD1602.setCursor(6, 0);  //光标移动到第1行的第10个字符开始显示
      LCD1602.print(BusVoltage_RGB_LED);
      LCD1602.setCursor(9, 0);  //光标移动到第1行的第12个字符开始显示
      LCD1602.print(" V");

      LCD1602.setCursor(0, 1);  //光标移动到第2行的第1个字符
      LCD1602.print("Shunt:");
      LCD1602.setCursor(9, 1);  //光标移动到第2行的第8个字符开始显示
      LCD1602.print(ShuntVoltage_RGB_LED);
      LCD1602.setCursor(12, 1);  //光标移动到第2行的第12个字符开始显示
      LCD1602.print(" mV");

      break;
    }
    case 21: { // RGB_LED 电流，功率
      LCD1602.setCursor(0, 0);  //光标移动到第1行的第1个字符开始显示
      LCD1602.print("Current: ");
      LCD1602.setCursor(9, 0);  //光标移动到第1行的第10个字符开始显示
      LCD1602.print(current_RGB_LED);
      LCD1602.setCursor(12, 0);  //光标移动到第1行的第12个字符开始显示
      LCD1602.print(" mA");

      LCD1602.setCursor(0, 1);  //光标移动到第2行的第1个字符
      LCD1602.print("Power:");
      LCD1602.setCursor(7, 1);  //光标移动到第2行的第8个字符开始显示
      LCD1602.print(power_RGB_LED);
      LCD1602.setCursor(11, 1);  //光标移动到第2行的第12个字符开始显示
      LCD1602.print(" mW");

      break;
    }

    case 30: { // semiconductor_cooling 电压，电源电压
      LCD1602.setCursor(0, 0);  //光标移动到第1行的第1个字符开始显示
      LCD1602.print("Bus: ");
      LCD1602.setCursor(6, 0);  //光标移动到第1行的第10个字符开始显示
      LCD1602.print(BusVoltage_semiconductor_cooling);
      LCD1602.setCursor(9, 0);  //光标移动到第1行的第12个字符开始显示
      LCD1602.print(" V");

      LCD1602.setCursor(0, 1);  //光标移动到第2行的第1个字符
      LCD1602.print("Shunt:");
      LCD1602.setCursor(9, 1);  //光标移动到第2行的第8个字符开始显示
      LCD1602.print(ShuntVoltage_semiconductor_cooling);
      LCD1602.setCursor(12, 1);  //光标移动到第2行的第12个字符开始显示
      LCD1602.print(" mV");

      break;
    }
    case 31: { // semiconductor_cooling 电流，功率
      LCD1602.setCursor(0, 0);  //光标移动到第1行的第1个字符开始显示
      LCD1602.print("Current: ");
      LCD1602.setCursor(9, 0);  //光标移动到第1行的第10个字符开始显示
      LCD1602.print(current_semiconductor_cooling);
      LCD1602.setCursor(12, 0);  //光标移动到第1行的第12个字符开始显示
      LCD1602.print(" mA");

      LCD1602.setCursor(0, 1);  //光标移动到第2行的第1个字符
      LCD1602.print("Power:");
      LCD1602.setCursor(7, 1);  //光标移动到第2行的第8个字符开始显示
      LCD1602.print(power_semiconductor_cooling);
      LCD1602.setCursor(11, 1);  //光标移动到第2行的第12个字符开始显示
      LCD1602.print(" mW");

      break;
    }
    default: {
      Serial.println("QwQ");
      break;
    }
  }

}