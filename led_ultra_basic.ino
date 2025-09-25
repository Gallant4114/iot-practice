// code untuk led dan ultrasonic

// Pin sensor ultrasonik
const int trigPin = 23;
const int echoPin = 21;

// Pin LED
const int ledPin = 13;

// Variabel untuk menghitung jarak
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Bersihkan sinyal trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Kirim pulsa 10µs
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca waktu pantulan
  duration = pulseIn(echoPin, HIGH);

  // Konversi ke jarak (cm)
  distance = duration * 0.034 / 2;

  // Tampilkan di Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Jika jarak ≤ 10 cm, nyalakan LED
  if (distance <= 10) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(200);
}
