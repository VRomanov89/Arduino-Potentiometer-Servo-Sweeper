#include <Servo.h>
Servo test;
int AnalogOut = 0;
int NewAnalogOut = 0;

void setup() {
  Serial.begin(9600);
  test.attach(11);
}
// test
void loop() {
  int sensorValue = analogRead(A0);
  
  NewAnalogOut = map(sensorValue, 0, 1023, 0, 180);
  Serial.print(AnalogOut);
  Serial.println(NewAnalogOut);
  if (abs(NewAnalogOut - AnalogOut) > 2) {
    test.write(AnalogOut);
    AnalogOut = NewAnalogOut;
  }
  delay(1);
  
}
