#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_CCS811.h>
#include <SoftwareSerial.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Adafruit_CCS811 ccs;

int moisturePin = A0;
int pumpPin = 8;

float chemicalValue1 = 0.0;
float chemicalValue2 = 0.0;
float chemicalValue3 = 0.0;
float pHValue = 0.0;

SoftwareSerial pHSerial(2, 3);

void setup() {
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
  pHSerial.begin(9600);
  
  if (!ccs.begin()) {
    Serial.println("Failed to start CCS811 gas sensor! Please check wiring.");
    while (1);
  }

  dht.begin();
}

void loop() {
  int moistureValue = analogRead(moisturePin);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (ccs.available()) {
    if (!ccs.readData()) {
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print(" ppm\t");
      Serial.print("TVOC: ");
      Serial.println(ccs.getTVOC());
    }
  }

  if (pHSerial.available()) {
    pHValue = pHSerial.parseFloat();
  }

  if (pHValue < 5.0 || pHValue > 7.0) {
    Serial.println("Warning: pH level is outside the healthy range (5.0-7.0).");
  }

  if (chemicalValue1 > 80.0 || chemicalValue2 > 60.0 || chemicalValue3 > 70.0) {
    Serial.println("Warning: Chemical values are above the healthy range for plants.");
  }

  if (moistureValue < 500) {
    digitalWrite(pumpPin, HIGH);
    Serial.println("Moisture level is low. Pump is turned on.");
  } else {
    digitalWrite(pumpPin, LOW);
    Serial.println("Moisture level is healthy. Pump is turned off.");
  }

  if (temperature < 15 || temperature > 30) {
    Serial.println("Warning: Temperature is out of the healthy range (15-30°C).");
  }

  if (humidity < 40 || humidity > 80) {
    Serial.println("Warning: Humidity is out of the healthy range (40-80%).");
  }

  delay(1000);
}
