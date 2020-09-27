#include <AFMotor.h>
#include <Servo.h>      
#include <NewPing.h>

#define OBS_DIST 20       //MIN DIST BETWEEN OBSTACE AND BOT (  in cm )

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int LMF = 7;        //LEFT MOTER CLOCKWISE
const int LMB = 8;        //LEFT MOTER ANTI-CLOCKWISE
const int RMF = 12;       //RIGHT MOTER CLOCKWISE
const int RMB = 13;       //RIGHT MOTER ANTI-CLOCKWISE
Servo myservo;

int leftDistance, rightDistance;
int curDist = 0;

void setup() {
  Serial.begin(9600);  
  myservo.attach(10);
  myservo.write(90);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LMF, OUTPUT);
  pinMode(LMB, OUTPUT);
  pinMode(RMF, OUTPUT);
  pinMode(RMB, OUTPUT);
 }
  
void loop() {
  myservo.write(90);
  delay(90);
  curDist = readPing();
  if (curDist < COLL_DIST)
    changePath();
  else
    moveForward();
  delay(500);
 }

int readPing() {
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  return distance;
}

void changePath() {
  moveStop();
  myservo.write(45);
    delay(500);
    rightDistance = readPing();
    delay(500);
    myservo.write(135);
    delay(500);
    leftDistance = readPing();
    delay(500);
    myservo.write(90);
    delay(100);
    if (leftDistance>=rightDistance)
      turnLeft();
    else if (rightDistance>leftDistance)
      turnRight();
  }

void moveForward() {
  digitalWrite(LMF,HIGH);
  digitalWrite(LMB,LOW);
  digitalWrite(RMF,HOGH);
  digitalWrite(RMB,LOW);
}

void turnRight() {
  digitalWrite(LMF,HIGH);
  digitalWrite(LMB,LOW);
  digitalWrite(RMF,LOW);
  digitalWrite(RMB,HIGH);
  delay(1000);
}  

void turnLeft() {
  digitalWrite(LMF,LOW);
  digitalWrite(LMB,HIGH);
  digitalWrite(RMF,HIGH);
  digitalWrite(RMB,LOW);
  delay(1000);
}  

void moveStop() {
   digitalWrite(LMF,LOW);
  digitalWrite(LMB,LOW);
  digitalWrite(RMF,LOW);
  digitalWrite(RMB,LOW);
}
