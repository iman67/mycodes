/*This code is about multitasking 
In this code yu cas see two leds works together and one servo works by condition that you setup.
*/
#include <LEDDisplay74HC595.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <Servo.h> 
//float voltage = 0.0;
const int sclkPin = 4;
const int rclkPin = 5;
const int dioPin = 6;
int ledPin = 13; //not used
int ledPin2 = 11; //not used
LEDDisplay74HC595 ledDisplay(sclkPin, rclkPin, dioPin);
///////////////////////////////////////////////////
Servo myservo;  // create servo object to control a servo
int angle =90;    // initial angle  for servo
int angleStep =1;

#define LEFT 12   // pin 12 is connected to left button
#define RIGHT  2  // pin 2 is connected to right button

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
  void reset()
  {
    pos = 0;
    servo.write(pos);
    increment = abs(increment);
  }

  void Update2() ///auto
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

  
  
  void Update()///gpio move
  {
    
    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();
      if (angle > 0 && angle <= 180) {
      angle = angle - angleStep;
      if(angle  < 0){
        angle =0;
       }else{
      servo.write(angle);
      //angle = angle + angleStep;
      //myservo.write(angle); // move the servo to desired angle
      Serial.print("Moved to: ");
      Serial.print(angle);   // print the angle
      Serial.println(" degree");
      
    
     
       }
      }
    }  
  }

  void Update3()
  {
    
    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();
      if (angle >= 0 && angle <= 180) {
      angle = angle + angleStep;
      if(angle  >180){
        angle =180;
       }else{
      servo.write(angle);
      //angle = angle + angleStep;
      //myservo.write(angle); // move the servo to desired angle
      Serial.print("Moved to: ");
      Serial.print(angle);   // print the angle
      Serial.println(" degree");
      
    
     
       }
      }
    }  
  }




  
};
/////////////////////////////////////////////  
Flasher led1(13, 123, 400);
/////////////////////////////////////////////

Sweeper sweeper1(45);



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
  // Servo button demo by Robojax.com
  Serial.begin(9600);          //  setup serial
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(LEFT,INPUT_PULLUP); // assign pin 12 ass input for Left button
  pinMode(RIGHT,INPUT_PULLUP);// assing pin 2 as input for right button
  myservo.write(angle);// send servo to the middle at 90 degrees
} 
 
// Interrupt is called once a millisecond, to update the LEDs
// Sweeper2 s not updated if the button on digital 2 is pressed.
SIGNAL(TIMER0_COMPA_vect) 
{
  sweeper1.Attach(10);
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
  if(voltage2 > 2.5)
  {
  digitalWrite(13, LOW);
  digitalWrite(11, LOW); 
  ////sweeper1.reset();
  //sweeper1.Detach();
  } 
  if
  (digitalRead(LEFT) == LOW)
  {
    sweeper1.Update3();
  }
  //(voltage2 > 5) digitalWrite(11, LOW);
  if
  (digitalRead(RIGHT) == LOW)
  {
    sweeper1.Update();
    //digitalWrite(13, HIGH);
  }
  if ((voltage2 > 2.5))
  {
     sweeper1.Update2();
  }
  
  if (voltage2 < 2.5) 
  {
     //sweeper1.Attach(10);
//     sweeper1.Update();
     led1.Update();
     //digitalWrite(13, HIGH);
     
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
