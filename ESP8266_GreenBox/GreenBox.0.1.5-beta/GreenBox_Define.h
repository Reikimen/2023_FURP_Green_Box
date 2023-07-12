///////////////////////////////////////////////////////// Headers /////////////////////////////////////////////////////////
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DFRobot_VEML7700.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

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


///////////////////////////////////////////////////// Variables for Output /////////////////////////////////////////////////////
// The variables for controlled output values, such as the speed of the wind (Global)
// Wind
int wind_force = 180;
// LIGHT
int LED_R = 255;
int LED_G = 255;
int LED_B = 0;
int LED_RGB_Brightness = 120;
int LED_kapa = 0;


