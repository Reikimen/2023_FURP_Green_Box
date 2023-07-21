double data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  data=(long)analogRead(0);
  data=(data/650)*4;
  Serial.print("the depth is:");
  Serial.print(data);
  Serial.println("cm");
  delay(1000);
}