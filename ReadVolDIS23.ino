// the setup routine runs once when you press reset:
#include <LEDDisplay74HC595.h>
//#include <TimerOne.h>
#include <TimerThree.h>
#include <Servo.h> 
//float voltage = 0.0;
const int sclkPin = 4;
const int rclkPin = 5;
const int dioPin = 6;
int ledPin = 13; //not used
int ledPin2 = 11; //not used
LEDDisplay74HC595 ledDisplay(sclkPin, rclkPin, dioPin);
//////////////////////////////////////////////////
class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time

  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated

  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  OnTime = on;
  OffTime = off;
  
  ledState = LOW; 
  previousMillis = 0;
  }

  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);   // Update the actual LED
    }
  }
};

///////////////////////////////////////////////

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
Flasher led1(11, 123, 400);
/////////////////////////////////////////////

Sweeper sweeper1(25);



void setup() {
  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);
  sweeper1.Attach(10);
  Timer3.initialize(5000);
  Timer3.attachInterrupt(refreshDisplay);
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
     led1.Update();
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
