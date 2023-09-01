#include <AccelStepper.h>
#include <HallSensor.h>

#define RPM_SENSOR_PIN 2
#define STEPS_PER_REV 200

AccelStepper stepper(1, 8, 9);

HallSensor rpmSensor(RPM_SENSOR_PIN);

const int targetRPM = 100;// your desired rpm:)

void setup() {
  stepper.setMaxSpeed(targetRPM * STEPS_PER_REV / 60);
  stepper.setAcceleration(1000);
  pinMode(RPM_SENSOR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  int currentRPM = rpmSensor.getRPM();

  if (currentRPM < targetRPM) {
    stepper.runSpeed();
  } else {
    stepper.stop();
  }

  Serial.print("Current RPM: ");
  Serial.println(currentRPM);
}
