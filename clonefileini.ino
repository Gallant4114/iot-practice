#include <WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

#define DHTPIN 17     // Pin untuk data sensor DHT22
#define DHTTYPE DHT22 // Menentukan jenis sensor DHT22

const char *ssid = "gantinamawifi";           // Nama WiFi Anda
const char *password = "gantipasswordwifi";         // Password WiFi Anda
unsigned long myChannelNumber = gantichannelidkalian;    // Channel ID ThingSpeak
const char *myWriteAPIKey = "gantiapiwritekalian";  // Write API Key ThingSpeak

WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);  // Inisialisasi sensor DHT22

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Tunggu hingga koneksi WiFi berhasil
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ThingSpeak.begin(client);  // Inisialisasi koneksi ThingSpeak
  dht.begin();  // Inisialisasi sensor DHT22
}

void loop() {
  // Membaca suhu dan kelembapan dari sensor DHT22
  float temperature = dht.readTemperature();  // Mengambil suhu dalam Celcius
  float humidity = dht.readHumidity();        // Mengambil kelembapan

  // Cek jika pembacaan gagal
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Tampilkan hasil ke serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C  ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Kirim data ke ThingSpeak
  ThingSpeak.setField(1, temperature);  // Field 1 untuk suhu
  ThingSpeak.setField(2, humidity);     // Field 2 untuk kelembapan
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  // Kirim data ke ThingSpeak

  delay(20000);  // Kirim data setiap 20 detik
}
