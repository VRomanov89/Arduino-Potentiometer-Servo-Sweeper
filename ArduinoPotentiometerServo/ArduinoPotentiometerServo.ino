#include <Servo.h>
Servo test;
int AnalogOut = 0;
int NewAnalogOut = 0;
int pin_Button = 12;
int pin_Button_State = 0;
int pin_Button_State_Last = 0;
int storage[800];
int storage_loc = 0;
int recording = 0;

int servo_Speed = 130;     //servo speed in RPM
int servo_Type = 180;      //360 for continuous

void setup() {
  Serial.begin(9600);
  test.attach(11);
  pinMode(pin_Button, INPUT);
  
  if(servo_Type == 360)
  {
    test.write(90);
  }
}
// testing
void loop() {
  if (recording == 0) {
    int sensorValue = analogRead(A0);
    NewAnalogOut = map(sensorValue, 0, 1023, 0, 180);
  //   if (abs(NewAnalogOut - AnalogOut) > 2) {
    if(servo_Type == 180)
    {
      test.write(AnalogOut);
    }
    else
    {
      if(NewAnalogOut-AnalogOut>0)
      {
        test.write(180);    //Rotate CW
        delay((((NewAnalogOut-AnalogOut)/360)/servo_Speed)*60000);
        test.write(90);     //Stop
      }
      else
      {
        test.write(0);      //Rotate CCW
        delay((((AnalogOut-NewAnalogOut)/360)/servo_Speed)*60000);
        test.write(90);     //Stop
      }
    }
    AnalogOut = NewAnalogOut;
  }
  delay(1);
  if ( recording == 1) {
    recording = 1;
    if (storage_loc < 1000) {
      storage[storage_loc] = NewAnalogOut;
      delay(100);
      Serial.println(storage[storage_loc]);
      storage_loc++;
    }
  } else if (recording > 1) {
    while (1 == 1) {
    storage_loc = 0;
    if (storage_loc < 1000 || storage[storage_loc] != 666) {
      test.write(storage[storage_loc]);
      delay(100);
    }
    }
  }

    pin_Button_State = digitalRead(pin_Button);
  if (pin_Button_State != pin_Button_State_Last) {
    if (pin_Button_State == HIGH) {
      recording++;
      if (recording == 2) {
        storage[storage_loc] = 666;
      }
    } else {
    }
    delay(50);
  }
  pin_Button_State_Last = pin_Button_State;
  
}
