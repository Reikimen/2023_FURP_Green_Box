//////////////////////////////////////////////////// WiFi ////////////////////////////////////////////////////
void WiFi_connection() {
  // WiFi STA
  WiFi.mode(WIFI_STA);                          // 以station模式连接WiFi
  WiFi.config(staticIP, gateway, subnet, dns);  // 配置静态IP地址
  WiFi.begin("XY-2758", "12345678");            // 连接WiFi

  int count_WiFi_connection = 0;
  while (WiFi.status() != WL_CONNECTED) {  // 如果没有连接到WiFi就持续输出...
    count_WiFi_connection = count_WiFi_connection + 1;
    Serial.println("...");
    if (count_WiFi_connection >= 300) {
      Serial.println("WiFi Connection failed");
      lcd_display_WiFi_connection_failed();
      break;
    }
    delay(200);
  }
  if (count_WiFi_connection < 300) {
    Serial.println(WiFi.localIP());
    lcd_display_IPaddress();
    delay(2000);
  }
}
