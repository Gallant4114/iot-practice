// Code untuk sensor ultrasonic, led, dan servo motor

#include <ESP32Servo.h>

// Pin ultrasonik
const int trigPin = 22;
const int echoPin = 21;

// Pin LED
const int ledPin = 23;

const int servoPin = 19;

long duration;
int distance;

Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(0);

  Serial.begin(115200);
}

void loop() {
  // Trigger sensor ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca pantulan
  duration = pulseIn(echoPin, HIGH);

  // Hitung jarak dalam cm (kecepatan suara = 343 m/s)
  distance = duration * 0.034 / 2;

  // Debug ke Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Kondisi: jika jarak <= 10 cm, LED ON
  if (distance <= 10) {
    digitalWrite(ledPin, HIGH);
    myServo.write(90);
    Serial.println("Lampu: Nyala dan gate buka");

  } else {
    digitalWrite(ledPin, LOW);
    myServo.write(0);
    Serial.println("Lampu: mati, servo: 0 derajat");
    }

  Serial.println("-------------------");
  delay(500);
}
