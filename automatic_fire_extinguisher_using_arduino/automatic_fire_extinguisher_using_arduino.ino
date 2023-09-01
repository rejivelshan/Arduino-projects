int flameSensorPin = A0;
int motor1Pin1 = 2;
int motor1Pin2 = 3;
int motor2Pin1 = 4;
int motor2Pin2 = 5;
int pumpPin = 6;
int flameThreshold = 400;

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int flameValue = analogRead(flameSensorPin);
  
  if (flameValue > flameThreshold) {
    extinguishFire();
    moveBackward();
    delay(1000);
    stopMoving();
  } else {
    moveForward();
  }
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void stopMoving() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void extinguishFire() {
  digitalWrite(pumpPin, HIGH);
  delay(5000);
  digitalWrite(pumpPin, LOW);
}
