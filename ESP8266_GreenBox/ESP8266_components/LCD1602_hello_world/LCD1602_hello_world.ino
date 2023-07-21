#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // 设置液晶地址 0x27  设置一行显示的字符 16个 2 行显示

void setup()
{
  lcd.init();                      //初始化
 
  // Print a message to the LCD.
  lcd.backlight();   //打开背光
  lcd.print("Hello, world!");  //输出内容
  delay(5000);
  lcd.clear();//清屏，准备显示新信息
  lcd.setCursor(0, 0);//光标移动到第1行的第1个字符开始显示
  lcd.print("Use Serial Mon");
  lcd.setCursor(0, 1);//光标移动到第2行的第1个字符
  lcd.print("Type to display");
}

void loop()
{
}

