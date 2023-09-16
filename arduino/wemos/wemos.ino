#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


const char* ssid = "Internetan Puas";
const char* password = "gratiskok";
String serverUrl = "http://192.168.16.124";



#define PZEM_RX_PIN D6 // Ubah pin sesuai dengan pin yang tersedia pada Wemos D1 R2
#define PZEM_TX_PIN D7 // Ubah pin sesuai dengan pin yang tersedia pada Wemos D1 R2


#include <DHT.h>
#define DHTPIN D5 // Ubah pin sesuai dengan pin yang tersedia pada Wemos D1 R2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial pzemSWSerial(PZEM_RX_PIN, PZEM_TX_PIN);
PZEM004Tv30 pzem(pzemSWSerial);

#define BUZZER_PIN D8 // Ubah pin sesuai dengan pin yang tersedia pada Wemos D1 R2

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27 // Alamat I2C untuk LCD biasanya adalah 0x3F

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

DynamicJsonDocument postData(1024);
DynamicJsonDocument tanggapanPostData(1024);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

int n = 1;
String suhu, tegangan = "Listrik Padam",kelembaban;
float volt = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  
  WiFi.begin(ssid, password);

  Serial.print("Menghubungkan ke ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Koneksi WiFi berhasil!");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  timeClient.setTimeOffset(0);
}

void loop() {
  ambiltegangan();
  bacasuhu();

  bacalcd(suhu, tegangan);
  upload();
  delay(2000);
}



void buzzer(int duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
  delay(duration);
}

void bacasuhu() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Gagal membaca data dari sensor DHT!");
    return;
  }

  suhu = String(temperature) + "C";
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.println(" °C");

  kelembaban = String(humidity)+"%RH";
  Serial.print("Kelembaban: ");
  Serial.print(humidity);
  Serial.println(" %");
}

void bacalcd(String nilai1, String nilai2) {

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Suhu:"+nilai1);

  lcd.setCursor(0, 1);
  if(nilai2 == "Listrik Padam") {
    lcd.print(nilai2);
  }else {
    lcd.print("Tegangan:"+nilai2);
  }
}

void ambiltegangan() {
  Serial.print("Custom Address:");
  Serial.println(pzem.readAddress(), HEX);

  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();

  if (isnan(voltage)) {
    Serial.println("Error reading voltage");
    tegangan = "Listrik Padam";
    volt = 0.00;
  } else if (isnan(current)) {
    Serial.println("Error reading current");
  } else if (isnan(power)) {
    Serial.println("Error reading power");
  } else if (isnan(energy)) {
    Serial.println("Error reading energy");
  } else if (isnan(frequency)) {
    Serial.println("Error reading frequency");
  } else if (isnan(pf)) {
    Serial.println("Error reading power factor");
  } else {

    tegangan = String(voltage) + "V";
    volt = voltage;
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println("V");
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println("A");
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println("W");
    Serial.print("Energy: ");
    Serial.print(energy, 3);
    Serial.println("kWh");
    Serial.print("Frequency: ");
    Serial.print(frequency, 1);
    Serial.println("Hz");
    Serial.print("PF: ");
    Serial.println(pf);
  }

  Serial.println();
}


void upload(){
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  String kirim = "";

  JsonObject datasensor = postData.to<JsonObject>();
  datasensor["suhu"] = suhu;
  datasensor["kelembaban"] = kelembaban;
  datasensor["tegangan"] = tegangan;
  datasensor["waktu"] = epochTime;

  HTTPClient http;
  WiFiClient client;
  String url = "/iotperbandingan/public/api/iot/data2";
  url = serverUrl + url;


  serializeJson(datasensor, kirim);

  Serial.println(kirim);

  client.connect(serverUrl, 80);
  http.begin(client, url);

  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(kirim);

//  Serial.println(httpResponseCode);
  
  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();
    deserializeJson(tanggapanPostData, response);

    JsonObject obj = tanggapanPostData.as<JsonObject>();
    String pesan = obj["pesan"].as<String>();

    if(volt > 230.00){
        buzzer(1000);
    }
  
    Serial.print(pesan);
    
  }else {
    Serial.print("Gagal mengambil data upload");
    Serial.println(http.errorToString(httpResponseCode));
  }

  
  tanggapanPostData.clear();
  postData.clear();
  
  
}
