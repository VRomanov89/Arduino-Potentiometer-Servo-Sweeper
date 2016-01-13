#include <Servo.h>
Servo test;
int AnalogOut = 0;
int NewAnalogOut = 0;
int pin_Button = 12;
int pin_Button_State;

void setup() {
  Serial.begin(9600);
  test.attach(11);
  pinMode(pin_Button, INPUT);
}
// test
void loop() {
  int sensorValue = analogRead(A0);
  
  NewAnalogOut = map(sensorValue, 0, 1023, 0, 180);
  pin_Button_State = digitalRead(pin_Button);
  Serial.println(pin_Button_State);
  if (abs(NewAnalogOut - AnalogOut) > 2) {
    test.write(AnalogOut);
    AnalogOut = NewAnalogOut;
  }
  delay(1);
  
}
