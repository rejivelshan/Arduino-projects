#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_CCS811.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Adafruit_CCS811 ccs;

int moisturePin = A0;
int pumpPin = 8;

void setup() {
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
  
  if (!ccs.begin()) {
    Serial.println("Failed to start CCS811 sensor! Please check wiring.");
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
