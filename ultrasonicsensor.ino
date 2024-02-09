#include "NewPing.h"

#define TRIGGER_PIN 7
#define ECHO_PIN 8

#define MAX_DISTANCE 10
#define MIN_DISTANCE 3

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  int distance = sonar.ping_cm();

 
  int percentVolume = map(distance, MIN_DISTANCE, MAX_DISTANCE, 100, 0);
  percentVolume = constrain(percentVolume, 0, 100); // Ensure the value is within the 0-100 range.

  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.print(" cm, ");
  Serial.print("Percentage Volume = ");
  Serial.print(percentVolume);
  Serial.println("%");

  delay(1000); 
}
