#include <ESP8266WiFi.h>        // 本程序使用 ESP8266WiFi库
#include <ESP8266WebServer.h>   //  ESP8266WebServer库
 
ESP8266WebServer esp8266_server(80);// 建立ESP8266WebServer对象，对象名称为esp8266_server
                                    // 括号中的数字是网路服务器响应http请求的端口号
                                    // 网络服务器标准http端口号为80，因此这里使用80为端口号

IPAddress staticIP(192, 168, 100, 100);  // esp8266开发板的固定IP地址
IPAddress gateway(192, 168, 100, 1);  // 网关地址，路由器的IP地址
IPAddress subnet(255, 255, 255, 0);  // 子网掩码
IPAddress dns(192, 168, 100, 1);  // dns服务器默认
IPAddress ComputerIP(192, 168, 50, 200);  // 电脑的IP

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // 连接WiFi
  WiFi.mode(WIFI_STA);  // 以station模式连接WiFi
  WiFi.config(staticIP, gateway, subnet, dns);  // 配置静态IP地址
  WiFi.begin("XY-2758", "12345678"); // 连接WiFi
  while (WiFi.status() != WL_CONNECTED) { // 如果没有连接到WiFi就持续输出...
    Serial.println("...");
    delay(250); // 延迟100m坤s
  }
  Serial.println(WiFi.localIP());

  //--------"启动网络服务功能"程序部分开始-------- 
  esp8266_server.begin();
  esp8266_server.on("/", handleRoot);       // ESP8266-NodeMCU网络服务器-1
  esp8266_server.onNotFound(handleNotFound);        
  //--------"启动网络服务功能"程序部分结束--------
  Serial.println("HTTP esp8266_server started");//  告知用户ESP8266网络服务功能已经启动
}

void loop() {
  // put your main code here, to run repeatedly:
  esp8266_server.handleClient();     // 处理http服务器访问
}
                                                                        
void handleRoot() {   //处理网站根目录“/”的访问请求 
  esp8266_server.send(200, "text/plain", "Hello Liang, ESP8266 Dankao Chen, 1");   // NodeMCU将调用此函数。
}
 
// 设置处理404情况的函数'handleNotFound'
void handleNotFound(){                                        // 当浏览器请求的网络资源无法在服务器找到时，
  esp8266_server.send(404, "text/plain", "404: Not found");   // NodeMCU将调用此函数。
}
