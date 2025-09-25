// Pin potensiometer
const int potPin = 34;   // ADC pin (input dari VOUT potensio)

// Pin LED
const int ledPin = 13;   // pin output PWM untuk LED

int potValue = 0;        // nilai ADC (0 - 4095)
int ledValue = 0;        // nilai PWM (0 - 255)

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // Baca nilai potensiometer (0 - 4095)
  potValue = analogRead(potPin);

  // Konversi ke range PWM (0 - 255)
  ledValue = map(potValue, 0, 4095, 0, 255);

  // Tulis nilai PWM ke LED
  analogWrite(ledPin, ledValue);

  // Debug di Serial Monitor
  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  |  LED PWM: ");
  Serial.println(ledValue);

  delay(200);
}
