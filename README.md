# Hands On Internet of Things

## A. Install Arduino IDE
Download dan install Arduino IDE pada [link berikut](https://www.arduino.cc/en/software)

Terdapat beberapa opsi untuk mendownload sesuai OS dan versi yang diperlukan.
![Screenshot 2024-12-07 180242](https://github.com/user-attachments/assets/ec16490e-4c52-47ca-bc76-b043d52cdb39)

Pada contoh berikut akan diberikan panduan untuk versi Windows. 

Berikut ini adalah file setup untuk instalasi. Lakukan install seperti pada umumnya.
![Screenshot 2024-12-07 180850](https://github.com/user-attachments/assets/b351f4f9-625f-4b92-b96f-9f155bc93238)

Setujui license agreement

![Screenshot 2024-12-07 181014](https://github.com/user-attachments/assets/ca7eb939-345a-4dbe-9651-a0992be441e5)
![Screenshot 2024-12-07 181303](https://github.com/user-attachments/assets/54906a22-b070-4c85-9168-f6680c1f1d75)

Pilih lokasi install

![Screenshot 2024-12-07 181141](https://github.com/user-attachments/assets/33b75cd3-c90d-414a-b252-2e060a070f8b)
![Screenshot 2024-12-07 181212](https://github.com/user-attachments/assets/88db306f-5668-4e79-8666-1ad3e5dc33d4)
![Screenshot 2024-12-07 182112](https://github.com/user-attachments/assets/a9441d28-060e-4f22-8b89-dc88c2130fff)

## B. Install Driver
Instalasi driver diperlukan agar dapat mengupload source code pada arduino. Download driver pada [link berikut](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)

![Screenshot 2024-12-07 184244](https://github.com/user-attachments/assets/900130b0-27fa-4007-b360-18fd8879c04f)

Pada contoh ini akan menggunakan **CP210x Universal Windows Driver**

![Screenshot 2024-12-07 185227](https://github.com/user-attachments/assets/0cc5ac1d-cca1-4c34-b2ba-704b43cfadc4)

Extract all pada folder instalasi Arduino IDE.

![Screenshot 2024-12-07 190750](https://github.com/user-attachments/assets/d18e0716-08cd-4ccc-918f-388de7a7bda5)

## C. Install Library yang dibutuhkan
Library dapat diinstall pada tab **Library Manager**. 

Pilih library sesuai kebutuhan, misalnya di sini adalah library untuk ESP32 dan Wifi.

![Screenshot 2024-12-07 192349](https://github.com/user-attachments/assets/7f4d2787-f6e6-428c-a159-f81197836125)
![Screenshot 2024-12-07 192402](https://github.com/user-attachments/assets/43cd2407-b6ab-4f9d-84e8-1a7844d80761)


## D. Selamat menjalankan code
```bash
#include <WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

#define DHTPIN 17     // Pin untuk data sensor DHT22
#define DHTTYPE DHT22 // Menentukan jenis sensor DHT22

const char *ssid = "gantinamawifi";                 // Nama WiFi Anda
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
```
