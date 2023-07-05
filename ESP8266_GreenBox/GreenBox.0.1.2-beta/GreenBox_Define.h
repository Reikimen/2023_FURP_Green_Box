/////////////////////////////////////////////////////// Hardwares ///////////////////////////////////////////////////////
// Set the PINs of the detectors and the controlled hardwares
// detectors
#define PIN_WATER A0
// CO2

// The Controlled hardwares's PIN DEFINE
// LED_PWM
// SG90_WIND
#define PIN_SG90_WIND 13  // GPIO 13 
Servo SG90_WIND;

// Set the address of the I2C hardwares
LiquidCrystal_I2C LCD1602(0x27,16,2); // Set the address of the LCD1602: 0x27
DFRobot_VEML7700 VEML7700;   // address is 0x10
#define Addr_SHT30 0x44   // SHT30 IIC 7-bit address is 0x44

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
// The controlled datas, such as the speed of the wind
int wind_force = 180;




