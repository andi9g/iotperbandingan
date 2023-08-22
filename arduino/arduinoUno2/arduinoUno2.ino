

#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

#define PZEM_RX_PIN 10
#define PZEM_TX_PIN 11
//dht konfigurasi

#include <DHT.h>
#define DHTPIN 5   // Pin D5 pada NodeMCU
#define DHTTYPE DHT11   // Tipe sensor DHT
DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial pzemSWSerial(PZEM_RX_PIN, PZEM_TX_PIN);
PZEM004Tv30 pzem(pzemSWSerial);


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#define I2C_ADDR 0x3F
#define I2C_ADDR 0x27

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

int n =1;
String suhu, tegangan="Listrik Padam";

void setup() {
    Serial.begin(115200);
    dht.begin();
}

void loop() {
    ambiltegangan();
    bacasuhu();
  
  
    bacalcd(suhu,tegangan);
    n++;
    delay(2000);
}


void bacasuhu() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Gagal membaca data dari sensor DHT!");
    return;
  }

  suhu = "Suhu:"+String(temperature)+"C";
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Kelembaban: ");
  Serial.print(humidity);
  Serial.println(" %");
}

void bacalcd(String nilai1, String nilai2){
  
  lcd.init();          // Inisialisasi LCD
  lcd.backlight();     // Aktifkan pencahayaan latar LCD
  lcd.clear(); 
  
  lcd.setCursor(0, 0); 
  lcd.print(nilai1);
  
  lcd.setCursor(0, 1); // Baris kedua, tengah
  lcd.print(nilai2);
}


void ambiltegangan(){
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

        tegangan = "Voltage:"+String(voltage)+"V";
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
        Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
        Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
        Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print("PF: ");           Serial.println(pf);
    }

    Serial.println();
}
