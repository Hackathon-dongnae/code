#include <Servo.h>
#define A1 0
#define A2 1
#define B1 2
#define B2 3
#define C1 4
#define C2 5
#define D1 6
#define D2 7
Servo servo,servo1;
int speed = 255, servoPin = 10, servoPin1 = 8,echoPin = 12,trigPin = 13,angle=0;;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position



void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  servo.attach(servoPin); 
  servo1.attach(servoPin1); 
}


void ultrasonic(){    //초음파 함수
  float duration, distance;
  
  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration = pulseIn(echoPin, HIGH); 
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  distance = ((float)(340 * duration) / 10000) / 2;  
  
  if(distance <=30){
      servo.write(359);
      servo1.write(359);
     delay(300); 
     servo.write(0);
      servo1.write(0);    
  }
  delay(1000);   
}

void loop() {
  ultrasonic(); //초음파 함수 호출
  
  while(Serial.available()>0){
    int value = Serial.parseInt();
    if(value == 1){                   // value == 1면 마스크를 쓴상태
      for (pos = 0; pos <= 105; pos += 1) { 
        // in steps of 1 degree
        myservo.write(pos);              
        delay(15);                       
      }
      for (pos = 105; pos >= 0; pos -= 1) { 
        myservo.write(pos);              
        delay(15);                       
      }      
    }
    else if(value == 2){              // value == 2면 마스크를 안쓴상태
      analogWrite(A2, speed);
      analogWrite(A1, 0);      
      analogWrite(B2, speed);
      analogWrite(B1, 0);
      analogWrite(C1, speed);
      analogWrite(C2, 0);      
      analogWrite(D1, speed);
      analogWrite(D2, 0);
      delay(1000);
      analogWrite(A1, 0);
      analogWrite(A2, 0);      
      analogWrite(B1, 0);
      analogWrite(B2, 0);
      analogWrite(C1, 0);
      analogWrite(C2, 0);      
      analogWrite(D1, 0);
      analogWrite(D2, 0);                    
    }
  }
}
