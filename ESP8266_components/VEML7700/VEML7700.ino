/*!
   @file readVEML770.ino
   @brief DFRobot's Digital Ambient Light Sensor
   @n This example read the Lux from Digital Ambient Light Sensor, and then print them

   @copyright   [DFRobot](https://www.dfrobot.com), 2016
   @copyright   GNU Lesser General Public License

   @version  V1.0
   @date  2016-12-06
*/


#include <Wire.h>
#include "DFRobot_VEML7700.h"

DFRobot_VEML7700 als;

void setup()
{
  Serial.begin(9600);
  als.begin();
}

void loop()
{
  float lux;
  als.getALSLux(lux);
  Serial.print("Lux: ");//Read Lux and print
  Serial.print(lux);
  Serial.println(" lx");
  delay(500);
}