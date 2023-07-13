///////////////////////////////////////////////////////// Headers /////////////////////////////////////////////////////////
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DFRobot_VEML7700.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <DFRobot_INA219.h>

/////////////////////////////////////////////////////// Hardwares ///////////////////////////////////////////////////////
// detectors
// Temp & humidity
#define Addr_SHT30 0x44   // SHT30 IIC 7-bit address is 0x44
// LIGHT
DFRobot_VEML7700 VEML7700;   // address is 0x10
// WATER
#define PIN_WATER A0
// CO2
#define CO2_SENSOR_DATA_PIN   (12)   // GPIO 12 (D6) Sensor PWM interface
#define INTERRUPT_NUMBER   digitalPinToInterrupt(CO2_SENSOR_DATA_PIN)   // interrupt number
// Wattmeter
//DFRobot_INA219_IIC     wattmeter_ina219(&Wire, INA219_I2C_ADDRESS3); // address3 是0x44 与SHT30 设置的重复了
DFRobot_INA219_IIC     wattmeter_ina219_fan(&Wire, INA219_I2C_ADDRESS1);
DFRobot_INA219_IIC     wattmeter_ina219_RGB_LED(&Wire, INA219_I2C_ADDRESS2);
DFRobot_INA219_IIC     wattmeter_ina219_semiconductor_cooling(&Wire, INA219_I2C_ADDRESS4);


// The output hardwares's DEFINE (WIND & LIGHT)
// LCD1602
LiquidCrystal_I2C LCD1602(0x27,16,2); // Set the address of the LCD1602: 0x27
// LED_WS2812
#define PIN_LED_RGB 14 // GPIO 14 (D5)
#define LED_RGB_NUMPIXELS 145 // 彩灯个数
Adafruit_NeoPixel LED_RGB(LED_RGB_NUMPIXELS, PIN_LED_RGB, NEO_GRB + NEO_KHZ800);
// SG90_WIND
#define PIN_SG90_WIND 13  // GPIO 13 (D7)
Servo SG90_WIND;

//////////////////////////////////////////////////////////// Datas ////////////////////////////////////////////////////////////
// The data from sensors (Global)
// sht30
unsigned int sht30_data[6]; //store the six acquired data of sht30 for temp and humidity
float sht30_cTemp = 0.0;
float sht30_fTemp = 0.0;
float sht30_humidity = 0.0;
// water depth
float water_depth = 0.0;
// Lightness
float VEML7700_light = 0.0;
// CO2
float CO2_pwm_high_val_ms = 0.0;
float CO2_concentration = 0.0;
volatile unsigned long CO2_pwm_high_start_ticks=0, CO2_pwm_high_end_ticks=0;// Used in interrupt, calculate pulse width variable
volatile unsigned long CO2_pwm_high_val=0, CO2_pwm_low_val=0;
volatile uint8_t CO2_flag=0;// interrupt flag
// Wattmeter 功率计
// Wattmeter 是否连接 flag, 0 表示未连接该 Wattmeter
int wattmeter_flag_fan = 0; 
int wattmeter_flag_RGB_LED = 0;
int wattmeter_flag_semiconductor_cooling = 0;
// Wattmeter 功率计校准
float ina219Reading_mA_fan = 1000; //Modify the variable in the code according to the current value printed by the serial port
float extMeterReading_mA_fan = 1000; //Modify the variables in the code according to the current value of the multimeter
float ina219Reading_mA_RGB_LED = 1000; //Modify the variable in the code according to the current value printed by the serial port
float extMeterReading_mA_RGB_LED = 1000; //Modify the variables in the code according to the current value of the multimeter
float ina219Reading_mA_semiconductor_cooling = 1000; //Modify the variable in the code according to the current value printed by the serial port
float extMeterReading_mA_semiconductor_cooling = 1000; //Modify the variables in the code according to the current value of the multimeter
// Wattmeter 示数 fan
float BusVoltage_fan = 0.0;
float ShuntVoltage_fan = 0.0;
float current_fan = 0.0;
float power_fan = 0.0;
// Wattmeter 示数 RGB_LED
float BusVoltage_RGB_LED = 0.0;
float ShuntVoltage_RGB_LED = 0.0;
float current_RGB_LED = 0.0;
float power_RGB_LED = 0.0;
// Wattmeter 示数 semiconductor_cooling
float BusVoltage_semiconductor_cooling = 0.0;
float ShuntVoltage_semiconductor_cooling = 0.0;
float current_semiconductor_cooling = 0.0;
float power_semiconductor_cooling = 0.0;


///////////////////////////////////////////////////// Variables for controlled Output /////////////////////////////////////////////////////
// The variables for controlled output values, such as the speed of the wind (Global)
// Wind
int wind_force = 180;
// LIGHT
int LED_R = 255;
int LED_G = 42;
int LED_B = 170;
int LED_RGB_Brightness = 120;
int LED_kapa = 0; //用于循环的一个个为LED赋值，for loop


