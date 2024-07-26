#include <Wire.h>

// Define pins for motor control
int diPin2 = 8; // Brake pin for motor 1
int pwmPin1 = 4; // PWM (Speed) pin for motor 1
int diPin1 = 5;  // Direction pin for motor 1

// Define pins for ultrasonic sensor
const int trigPin = 2; // Digital pin 7 for trigger
const int echoPin = 3; // Digital pin 8 for echo

// Define variables
long duration;
int distance;

void setup() {
  pinMode(diPin1, OUTPUT);
  pinMode(diPin2, OUTPUT);
  pinMode(pwmPin1, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); // Initialize serial communication
}

void moveforw() {
  Serial.println("Moving forward");
  digitalWrite(diPin1, HIGH);
  digitalWrite(diPin2, LOW);
  analogWrite(pwmPin1, 120);
}

void moveback() {
  Serial.println("Moving back");
  digitalWrite(diPin2, HIGH);
  digitalWrite(diPin1, LOW);
  analogWrite(pwmPin1, 120);
  delay(5000); // Adjust delay based on your requirements
  moveforw();
}

void breakit() {
  Serial.println("Breaking");
  digitalWrite(diPin1, LOW);
  digitalWrite(diPin2, LOW);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delay(2000);
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = (duration / 2)/29.1;

  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 20) {
    // If obstacle detected, stop the motors
    breakit();
    delay(3000); // Adjust delay based on your requirements
    moveback();
  } else {
    moveforw();
  }
}
