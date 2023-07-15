#include "GreenBox_Define.h"
#include "GreenBox_Function.h"
void setup() {
  setup_function();
  delay(2000); // the time used to setup
}
void loop() {
  loop_function();
  delay(500); // 500 milliseconds as a unit of time measurement
}