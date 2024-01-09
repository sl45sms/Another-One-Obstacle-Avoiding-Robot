
// Another One Obstacle Avoiding Robot
// inpired from varius Obstacle Avoiding Robots in Arduino Project Hub.
// works with DFROBOT DRI004 dual motor driver, and the usual stuff, SG90 servo, HC-SR04 Ultrasonic Distance Sensor 
// required libraries - Servo for the servo, NewPing for the Ultrasonic sensor

//TODO ArduinoBlue https://sites.google.com/stonybrook.edu/arduinoble or https://play.google.com/store/apps/details?id=com.shevauto.remotexy.pro


#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 

#define MAX_DISTANCE 200 
#define MAX_SPEED 190 // sets speed  of DC  motors
#define MAX_SPEED_OFFSET 20
#define SERVO_PIN 8
#define SERVO_LOOK_F 115

#define MOTOR1DIR 4 
#define MOTOR1PWM 5
#define MOTOR2DIR 7 
#define MOTOR2PWM 6

NewPing sonar(TRIG_PIN, ECHO_PIN,  MAX_DISTANCE); 

Servo  myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet  = 0;

void setup() {

  myservo.attach(SERVO_PIN);  
  myservo.write(SERVO_LOOK_F);
  delay(2000);
  distance = readPing();
  delay(100);
  distance =  readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance  = readPing();
  delay(100);
}

void loop() {
 int distanceR = 0;
  int distanceL =  0;
 delay(40);
 
 if(distance<=15)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
  }
 distance = readPing();
}

int lookRight()
{
    myservo.write(50);  
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115);  
    return distance;
}

int lookLeft()
{
    myservo.write(170);  
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115);  
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==1)
  {
    cm = 250;
  }
  return  cm;
}

void moveStop() {
  move(1,0,'f'); // moves motor 1 [left motor] forward at speed
  move(2,0,'f'); // moves motor 2 [right motor] forward at speed
  }
  
void moveForward()  {

 if(!goesForward)
  {
   goesForward=true;
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring  the speed up to avoid loading down the batteries too quickly
   {
   move(1,speedSet,'f'); // moves motor 1 [left motor] forward at speed
   move(2,speedSet,'f'); // moves motor 2 [right motor] forward at speed
    delay(5);
   }
  }
}

void moveBackward() {
  goesForward=false;
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet  +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    move(1,speedSet,'b'); // moves motor 1 [left motor] backward at speed
    move(2,speedSet,'b'); // moves motor 2 [right motor] backward at speed    
    delay(10);
  }
}  

void turnRight()  {
  moveStop();delay(500);
  move(1,100,'f'); // moves motor 1 [left motor] backward at speed
  move(2,100,'b'); // moves motor 2 [right motor] backward at speed
  delay(900);
      
} 
 
void turnLeft() {
  moveStop();delay(500);
  move(1,100,'b'); // moves motor 1 [left motor] backward at speed
  move(2,100,'f'); // moves motor 2 [right motor] backward at speed
  delay(900);
}  


// move the selectedmotor
void move(int motor, int speed, char direction){

  boolean motorDirectionPin;

  switch (direction) { 
    case 'f':
      motorDirectionPin = HIGH;
      break;
    case 'b':
      motorDirectionPin = LOW;
      break;
    default:
      motorDirectionPin = HIGH;
    break;
  }
  switch (motor) { 
    case 1:
      digitalWrite(MOTOR1DIR, motorDirectionPin);
      analogWrite(MOTOR1PWM, speed);
      break;
    case 2:
      digitalWrite(MOTOR2DIR, motorDirectionPin);
      analogWrite(MOTOR2PWM, speed);
      break;
  }
}
