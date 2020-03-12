// Robotics with the BOE Shield - MovementsWithSimpleFunctions
// Move forward, left, right, then backward for testing and tuning.

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
//****************************************
int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;
const int ledPin = 13;
//****************************************
 
 
void setup()                                 // Built-in initialization block
{ 
//**************************************
     pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, HIGH);
   
   while (millis() < 5000) {
     
   sensorValue = analogRead(A0);
   if (sensorValue > sensorHigh){
    sensorHigh = sensorValue;
  }
   if (sensorValue < sensorLow){
    sensorLow = sensorValue;
  }
}

digitalWrite(ledPin, LOW);
//****************************************
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  servoLeft.attach(13);                      // Attach left signal to P13 
  servoRight.attach(12);                     // Attach right signal to P12

  forward(60000);                             // Go forward for 60 seconds
  if(sensorLow < 55 ){
    turnLeft(600);    
  } else {
    forward(60000); 
  }
  if ( sensorHigh > 3000){
    turnRight(700);
  } else {
    forward(60000); 
  }
  backward(3000);
  disableServos();                           // Stay still indefinitely
}  
 
void loop()                                  // Main loop auto-repeats
{  // Empty, nothing needs repeating
//****************************************
   sensorValue = analogRead(A0);
   
   int pitch = map(sensorValue, sensorLow, sensorHigh,  50, 4000);
   tone(8, pitch, 20);
   delay (10);
//****************************************
                            // Go forward for 60 seconds
  if(sensorLow < 55 ){
    turnLeft(600);    
  } else {
    forward(60000); 
  }
  if ( sensorHigh > 3000){
    turnRight(700);
  } else {
    forward(60000);
  }
}

void forward(int time)                       // Forward function
{
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  delay(time);                               // Maneuver for time ms
}

void turnLeft(int time)                      // Left turn function
{
  servoLeft.writeMicroseconds(1300);         // Left wheel clockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  delay(time);                               // Maneuver for time ms
}

void turnRight(int time)                     // Right turn function
{
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700);        // Right wheel counterclockwise
  delay(time);                               // Maneuver for time ms
}

void backward(int time)                      // Backward function
{
  servoLeft.writeMicroseconds(1300);         // Left wheel clockwise
  servoRight.writeMicroseconds(1700);        // Right wheel counterclockwise
  delay(time);                               // Maneuver for time ms
}

void disableServos()                         // Halt servo signals
{                                            
  servoLeft.detach();                        // Stop sending servo signals
  servoRight.detach(); 
}
