/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/

// the setup routine runs once when you press reset:
#include <LEDDisplay74HC595.h>
#include <TimerOne.h>
#include <Servo.h> 
#include "TimerTwo.h"
//float voltage = 0.0;
const int sclkPin = 4;
const int rclkPin = 5;
const int dioPin = 6;
int ledPin = 13; //not used
int ledPin2 = 11; //not used
LEDDisplay74HC595 ledDisplay(sclkPin, rclkPin, dioPin);
//////////////////////////////////////////////////

class Sweeper
{
  Servo servo;              // the servo
  int pos;              // current servo position 
  int increment;        // increment to move for each interval
  int  updateInterval;      // interval between updates
  unsigned long lastUpdate; // last update of position

public: 
  Sweeper(int interval)
  {
    updateInterval = interval;
    increment = 1;
  }
  
  void Attach(int pin)
  {
    servo.attach(pin);
  }
  
  void Detach()
  {
    servo.detach();
  }
  
  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      Serial.println(pos);
      if ((pos >= 180) || (pos <= 0)) // end of sweep
      {
        // reverse direction
        increment = -increment;
      }
    }
  }
};
/////////////////////////////////////////////  

Sweeper sweeper1(45);



void setup() {
  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);
  sweeper1.Attach(8);
  Timer1.initialize(5000);
  Timer1.attachInterrupt(refreshDisplay);
  pinMode(ledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue2 = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage2 = sensorValue2 * (5.0 / 1023.0);
  // print out the value you read:
  //Serial.println(voltage2);
  
  {
  if
  (voltage2 > 2.5) digitalWrite(13, LOW);  
  //if
  //(voltage2 > 5) digitalWrite(11, LOW);
  //if
  //(voltage2 < 4.5) digitalWrite(13, LOW);
  if (voltage2 < 2.5) 
  {
     sweeper1.Update();
     digitalWrite(13, HIGH);
     
  }
  }
}
 
void refreshDisplay() {
  
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  //Serial.println(voltage);
  ledDisplay.refresh(voltage, 1);
  
}
