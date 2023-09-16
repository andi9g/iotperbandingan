#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#include <NTPClient.h>
#include <WiFiUdp.h>

#define pinD8 D8


#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

//dht konfigurasi
#include <DHT.h>
#define DHTPIN 14   // Pin D5 pada NodeMCU
#define DHTTYPE DHT11   // Tipe sensor DHT
DHT dht(DHTPIN, DHTTYPE);


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#define I2C_ADDR 0x3F
#define I2C_ADDR 0x27

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);


//baca watt
//SoftwareSerial pzemSerial(D6, D7); // RX, TX
//SoftwareSerial mySerial(12, 13);
SoftwareSerial pzemSWSerial(13, 12);
PZEM004Tv30 pzem;



const char* ssid = "Internetan Puas";
const char* password = "gratiskok";
String serverUrl = "http://192.168.124.124";

DynamicJsonDocument postData(1024);
DynamicJsonDocument tanggapanPostData(1024);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

String suhu, kelembaban, tegangan;
float volt = 0;
int n=1;


void setup() {
  Serial.begin(115200);
  dht.begin();
  pzem = PZEM004Tv30(pzemSWSerial);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  timeClient.setTimeOffset(0);

  pinMode(pinD8, OUTPUT);
  
}

void loop() {
  
  bacasuhu();
  bacawatt();
  
  bacalcd(suhu,tegangan);
  upload();
  
  delay(2000);
}

void buzzer(int duration) {
  digitalWrite(pinD8, HIGH); // Hidupkan buzzer
  delay(duration);
  digitalWrite(pinD8, LOW); // Matikan buzzer
  delay(duration);
}

void bacalcd(String nilai1, String nilai2){
  Wire.begin(D2, D1);  // Menginisialisasi I2C dengan pin SDA (D2) dan pin SCL (D1)
  lcd.init();          // Inisialisasi LCD
  lcd.backlight();     // Aktifkan pencahayaan latar LCD
  lcd.clear(); 
  
  lcd.setCursor(0, 0); 
  lcd.print("Suhu:"+nilai1);
  
  lcd.setCursor(0, 1); // Baris kedua, tengah
  if(nilai2 == "Listrik Padam") {
    lcd.print(nilai2);
  }else {
    lcd.print("Tegangan:"+nilai2);
  }
  
}


void bacasuhu() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Gagal membaca data dari sensor DHT!");
    return;
  }

  suhu = String(temperature)+"C";
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.println(" °C");
  kelembaban = String(humidity)+"%RH";
  Serial.print("Kelembaban: ");
  Serial.print(humidity);
  Serial.println(" %");
}


void bacawatt() {
  Serial.print("Custom Address:");
    Serial.println(pzem.readAddress(), HEX);
    // Read the data from the sensor
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    // Check if the data is valid
    if(isnan(voltage)){
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

        tegangan = String(voltage)+"V";
        volt = voltage;
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
        Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
        Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
        Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print("PF: ");           Serial.println(pf);

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
  String url = "/iotperbandingan/public/api/iot/data";
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
