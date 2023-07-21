/*
 * ws2812b
 * ESP8266驱动WS2812彩灯
 * 板载接口GPIO0
 */

#include <Adafruit_NeoPixel.h>

#define PIN        14  //D5接口
#define NUMPIXELS  15  //彩灯个数

Adafruit_NeoPixel led(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int kapa = 0;

void setup() {

  led.begin();
  led.setBrightness(255); //设置亮度 (0~255)
}

void loop() {
  for (kapa = 0; kapa < 15; kapa = kapa + 1){
    led.setPixelColor(kapa,led.Color(255, 0, 0)); //红色
    led.show(); //刷新显示
  }
  delay(1000);
  
  for (kapa = 0; kapa < 15; kapa = kapa + 1){
    led.setPixelColor(kapa,led.Color(0, 255, 0)); //绿色
    led.show(); //刷新显示
  }
  delay(1000);

  for (kapa = 0; kapa < 15; kapa = kapa + 1){
    led.setPixelColor(kapa,led.Color(0, 0, 255)); //蓝色
    led.show(); //刷新显示
  }
  delay(1000);

  for (kapa = 0; kapa < 15; kapa = kapa + 1){
    led.clear();//清空显示
    led.show(); //刷新显示
  }
  delay(1000);

}
