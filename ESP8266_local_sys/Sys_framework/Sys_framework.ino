#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the address of the I2C hardwares
LiquidCrystal_I2C LCD1602(0x27,16,2); // Set the address of the LCD1602: 0x27
#define Addr_SHT30 0x44   // SHT30 IIC 7-bit address is 0x44

// Set the PINs of the detectors and the controlled hardwares
// CO2


// The data from sensors
// sht30
unsigned int sht30_data[6]; //store the six acquired data of sht30 for temp and humidity
float sht30_cTemp = 0.0;
float sht30_fTemp = 0.0;
float sht30_humidity = 0.0;

void lcd_init(){
  LCD1602.init();
  LCD1602.backlight();
  LCD1602.print("Hello, world!");
  delay(2000);
  LCD1602.clear();
}


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

void lcd_display(){
  LCD1602.clear();

  // sht30, 需要后续调整具体LCD输出位置
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
  LCD1602.setCursor(11, 0);//光标移动到第1行的第12个字符开始显示
  LCD1602.print(" RH%");
  delay(1000);

  // CO2 & light

  delay(100);
}


void setup() {
  // put your setup code here, to run once:
  // ESP8266 initialization
  Wire.begin(); // init the I2C, if a problem is faced hear, use Wire.begin(SDA_PIN, SCL_PIN); 
  Serial.begin(9600);

  // hardware initialization
  lcd_init();

  delay(100); // the time used to setup
}

void loop() {
  // put your main code here, to run repeatedly:
  measure_sht30(); // about 100 ms
  lcd_display();
}
