void setup()
{
 Serial.begin(9600); //指定串口通讯比特率为9600
}
void loop()
//光量子传感器输出0-5V 外接电路转换为0-1V
 int v = analogRead(A0); //从A0口读取电压，模拟端口电压测量范围为0-1V，返回的值为0-1024
 Serial.println(v); //串口输出电压值
 float volt = v * (5.0 / 1024.0); //将返回值换算成传感器输出电压
 Serial.print(volt); //串口输出电压值
 Serial.println(" V"); //输出单位，并且换行
 float radio = volt * 500;
 Serial.println(radio); //串口输出电压值
 delay(1000); //输出后等待1s，降低刷新速度
}