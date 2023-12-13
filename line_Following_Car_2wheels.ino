#include <AFMotor.h>

AF_DCMotor motor_R(4);
AF_DCMotor motor_L(1);

#define sensorRight A5
#define sensorLeft A0
#define echo A2
#define trig A1

int speed;

void setup() {
  pinMode(sensorRight, INPUT);
  pinMode(sensorLeft, INPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  motor_R.setSpeed(speed);
  motor_L.setSpeed(speed);

  int rightSensorValue = digitalRead(sensorRight);
  int leftSensorValue = digitalRead(sensorLeft);


  if (ultraSound() < 30) {
    stop();
  } else {
    if (leftSensorValue == HIGH && rightSensorValue == HIGH) {
      stop();
    } else if (leftSensorValue == LOW && rightSensorValue == LOW) {
      forward();
    } else if (leftSensorValue == LOW && rightSensorValue == HIGH) {
      right();
    } else if (leftSensorValue == HIGH && rightSensorValue == LOW) {
      left();
    }
  }
}

void forward() {
  speed = 120;
  motor_R.run(FORWARD);
  motor_L.run(FORWARD);
}

void backward() {
  motor_R.run(BACKWARD);
  motor_L.run(BACKWARD);
}

void right() {
  speed = 80;
  motor_R.run(BACKWARD);
  motor_L.run(FORWARD);
}

void left() {
  speed = 80;
  motor_R.run(FORWARD);
  motor_L.run(BACKWARD);
}

void stop() {
  motor_R.run(RELEASE);
  motor_L.run(RELEASE);
}

int ultraSound() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float time = pulseIn(echo, HIGH);
  int distance = time * 0.034 / 2;
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}