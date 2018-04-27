#include <NewPing.h>

NewPing sonar1(13, 12, 100); // Sensor 1: trigger pin, echo pin, maximum distance in cm
NewPing sonar2(5, 6, 100); // Sensor 2: same stuff
#define pingSpeed 100
const int motorPin1  = 4;  // Pin 14 of L293
const int motorPin2  = 3;  // Pin 10 of L293
//Motor B
const int motorPin3  = 7; // Pin  7 of L293
const int motorPin4  = 8;  // Pin  2 of L293
const int enB = 9;
unsigned long pingTimer1, pingTimer2;
int in1, in2;
// defines variables
long duration;
long duration2;
int distance;
int distance2;
int pwm = 100;
void setup() {
  pingTimer1 = millis() + pingSpeed; // Sensor 1 fires after 100ms (pingSpeed)
  pingTimer2 = pingTimer1 + (pingSpeed / 2); // Sensor 2 fires 50ms later
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enB, OUTPUT);
  Serial.begin(9600);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW); 
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW); 
}
void  ping(){
   if (millis() >= pingTimer1) {
      pingTimer1 += pingSpeed; // Make sensor 1 fire again 100ms later (pingSpeed)
      in1 = sonar1.ping_cm();
   }
   if (millis() >= pingTimer2) {
      pingTimer2 = pingTimer1 + (pingSpeed / 2); // Make sensor 2 fire again 50ms after sensor 1 fires
      in2 = sonar2.ping_cm();
       // Both sensors pinged, process results here
   }
}
void loop() {
   ping();
   Serial.print("Sensor1: ");
   Serial.print(in1);
   Serial.println();
   Serial.print("Sensor2: ");
   Serial.print(in2);
   Serial.println();
   if(in1 == 0 && in2 == 0){
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      analogWrite(enB, pwm);
   }else if(in1 < 40 && (in2 == 0 || in2 > 40)){
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      delay(2000);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
   }else if(in2 < 40 && (in1 == 0 || in1 > 40)){
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      delay(2000);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
   }else if((in1 < 20 && in2 < 20) && (in1 > 0 && in2 > 0)){
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin1, LOW);
        analogWrite(enB, pwm + 70);
        delay(350);
        analogWrite(enB, 0);
        while((in1 < 20 && in2 < 20)){
          ping();  
        };  
   }
}
