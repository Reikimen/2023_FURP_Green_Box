// 校准SG90位置

#include<Servo.h>
//constexpr auto SERVO_1_PIN=9;
#define SERVO_1_PIN 13//舵机引脚

Servo SERVO_1;

void setup(){
  // put your setup code here, to run once:
  SERVO_1.attach(SERVO_1_PIN);//定义舵机名称已经对应引脚
  Serial.begin(115200);//115200
  
}
 
void loop(){
  // put your main code here, to run repeatedly:
  //SERVO_1.write(179);
  //delay(2000);//停顿2秒
  SERVO_1.write(0);
  delay(5000);//停顿5秒

  
}
