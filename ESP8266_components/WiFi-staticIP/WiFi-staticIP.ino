#include <ESP8266WiFi.h>

IPAddress staticIP(192, 168, 100, 100);  // esp8266开发板的固定IP地址
IPAddress gateway(192, 168, 100, 1);  // 网关地址，路由器的IP地址
IPAddress subnet(255, 255, 255, 0);  // 子网掩码
IPAddress dns(192, 168, 100, 1);  // dns服务器默认
IPAddress ComputerIP(192, 168, 50, 200);  // 电脑的IP

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // 以station模式连接WiFi
  WiFi.config(staticIP, gateway, subnet, dns);  // 配置静态IP地址
  WiFi.begin("XY-2758", "12345678"); // 连接WiFi
  while (WiFi.status() != WL_CONNECTED) { // 如果没有连接到WiFi就持续输出...
    Serial.println("...");
    delay(250); // 延迟100m坤s
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(WiFi.localIP());
  delay(3000);
}
