// 删除了不必要的代码部分——2023/7/6——cdk
#define CO2_SENSOR_DATA_PIN   (12)   // D6 Sensor PWM interface
#define INTERRUPT_NUMBER   digitalPinToInterrupt(CO2_SENSOR_DATA_PIN)   // interrupt number

// Used in interrupt, calculate pulse width variable
volatile unsigned long CO2_pwm_high_start_ticks=0, CO2_pwm_high_end_ticks=0;
volatile unsigned long CO2_pwm_high_val=0, CO2_pwm_low_val=0;
// interrupt flag
volatile uint8_t CO2_flag=0;

IRAM_ATTR void CO2_InterruptFunc()
//void interrupt_change()
{
  if (digitalRead(CO2_SENSOR_DATA_PIN)) {
    CO2_pwm_high_start_ticks = micros();    // store the current micros() value
    if(2 == CO2_flag){
      CO2_flag = 4;
      if(CO2_pwm_high_start_ticks > CO2_pwm_high_end_ticks) {
        CO2_pwm_low_val = CO2_pwm_high_start_ticks - CO2_pwm_high_end_ticks;
      }
    }else{
      CO2_flag = 1;
    }
  } else {
    CO2_pwm_high_end_ticks = micros();    // store the current micros() value
    if(1 == CO2_flag){
      CO2_flag = 2;
      if(CO2_pwm_high_end_ticks > CO2_pwm_high_start_ticks){
        CO2_pwm_high_val = CO2_pwm_high_end_ticks - CO2_pwm_high_start_ticks;
      }
    }
  }
}

void measure_CO2()
{
    if(CO2_flag == 4){
    CO2_flag = 1;
    float CO2_pwm_high_val_ms = (CO2_pwm_high_val * 1000.0) / (CO2_pwm_low_val + CO2_pwm_high_val);

    if (CO2_pwm_high_val_ms < 0.01){
      Serial.println("Fault");
    }
    else if (CO2_pwm_high_val_ms < 80.00){
      Serial.println("preheating");
    }
    else if (CO2_pwm_high_val_ms < 998.00){
      float CO2_concentration = (CO2_pwm_high_val_ms - 2) * 5;
      // Print pwm_high_val_ms
      Serial.print("CO2_pwm_high_val_ms:");
      Serial.print(CO2_pwm_high_val_ms);
      Serial.println("ms");
      //Print CO2 concentration
      Serial.print(CO2_concentration);
      Serial.println("ppm");
    }else{
      Serial.println("Beyond the maximum range : 398~4980ppm");
    }
    Serial.println();
  }
}