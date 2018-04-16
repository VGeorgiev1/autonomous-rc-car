const int trigPin = 10;
const int echoPin = 11;

const int motorPin1  = 4;  // Pin 14 of L293
const int motorPin2  = 3;  // Pin 10 of L293
const int enA = 9;
//Motor B
const int motorPin3  = 6; // Pin  7 of L293
const int motorPin4  = 7;  // Pin  2 of L293
const int enB = 8;
// defines variables
long duration;
int distance;
int pwm = 200;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enB, OUTPUT);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW); 
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(4);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  if(distance < 30){
    if(digitalRead(motorPin2) == HIGH){
      analogWrite(enA, 0);
      delay(700);
    }else{
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin1, LOW);
      analogWrite(enA, 180);
      delay(350);
      analogWrite(enA, 0);
    }    
  }else{
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    analogWrite(enA, 180);
  }
 
}
