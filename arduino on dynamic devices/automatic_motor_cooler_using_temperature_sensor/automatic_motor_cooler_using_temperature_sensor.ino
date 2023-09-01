#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define FAN_PIN 3
#define MOTOR_TEMP_THRESHOLD 40.0

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from sensor!");
    delay(1000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (temperature > MOTOR_TEMP_THRESHOLD) {
    digitalWrite(FAN_PIN, HIGH);
    Serial.println("Fan is ON. Cooling motor.");
  } else {
    digitalWrite(FAN_PIN, LOW);
    Serial.println("Fan is OFF. Motor temperature is normal.");
  }

  delay(1000);
}
