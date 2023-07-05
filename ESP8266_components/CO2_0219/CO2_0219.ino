#if defined(ESP32) || defined(ESP8266)
  // D7 pin is used as interrupt pin by default, other non-conflicting pins can also be selected as external interrupt pins.
  #define SENSOR_DATA_PIN   (13)   // Sensor PWM interface
  #define INTERRUPT_NUMBER   digitalPinToInterrupt(SENSOR_DATA_PIN)   // interrupt number
#elif defined(ARDUINO_SAM_ZERO)
  // Pin 5 is used as interrupt pin by default, other non-conflicting pins can also be selected as external interrupt pins
  #define SENSOR_DATA_PIN   (5)   // Sensor PWM interface
  #define INTERRUPT_NUMBER   digitalPinToInterrupt(SENSOR_DATA_PIN)   // interrupt number
#else
  // Open the external interrupt 0, connect INT1/2 to the digital pin of the main control: 
  // UNO(2), Mega2560(2), Leonardo(3), microbit(P0).
  #define SENSOR_DATA_PIN   (2)   // Sensor PWM interface
  #define INTERRUPT_NUMBER   (0)   // interrupt number
#endif


// Used in interrupt, calculate pulse width variable
volatile unsigned long pwm_high_start_ticks=0, pwm_high_end_ticks=0;
volatile unsigned long pwm_high_val=0, pwm_low_val=0;
// interrupt flag
volatile uint8_t flag=0;

IRAM_ATTR void InterruptFunc()
//void interrupt_change()
{
  if (digitalRead(SENSOR_DATA_PIN)) {
    pwm_high_start_ticks = micros();    // store the current micros() value
    if(2 == flag){
      flag = 4;
      if(pwm_high_start_ticks > pwm_high_end_ticks) {
        pwm_low_val = pwm_high_start_ticks - pwm_high_end_ticks;
      }
    }else{
      flag = 1;
    }
  } else {
    pwm_high_end_ticks = micros();    // store the current micros() value
    if(1 == flag){
      flag = 2;
      if(pwm_high_end_ticks > pwm_high_start_ticks){
        pwm_high_val = pwm_high_end_ticks - pwm_high_start_ticks;
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("beginning...");
  pinMode(SENSOR_DATA_PIN, INPUT);
  attachInterrupt(INTERRUPT_NUMBER, InterruptFunc, CHANGE);
}

void loop() {
  if(flag == 4){
    flag = 1;
    float pwm_high_val_ms = (pwm_high_val * 1000.0) / (pwm_low_val + pwm_high_val);

    if (pwm_high_val_ms < 0.01){
      Serial.println("Fault");
    }
    else if (pwm_high_val_ms < 80.00){
      Serial.println("preheating");
    }
    else if (pwm_high_val_ms < 998.00){
      float concentration = (pwm_high_val_ms - 2) * 5;
      // Print pwm_high_val_ms
      Serial.print("pwm_high_val_ms:");
      Serial.print(pwm_high_val_ms);
      Serial.println("ms");
      //Print CO2 concentration
      Serial.print(concentration);
      Serial.println("ppm");
    }else{
      Serial.println("Beyond the maximum range : 398~4980ppm");
    }
    Serial.println();
  }

  delay(1000);
}