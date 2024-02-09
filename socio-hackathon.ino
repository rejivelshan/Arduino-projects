    /*
  YF-S201-Water-Flow-Sensor
  made on 14 oct 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home

*/

double flow; //Liters of passing water volume
unsigned long pulse_freq;
int sensorPin = A0; 
int sensorValue;  
int limit = 300; 

void setup()
{
  pinMode(2, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, pulse, RISING); // Setup Interrupt
  
}

void loop ()
{
    flow = .00225 * pulse_freq;
    Serial.print(flow, DEC);
    Serial.println("L");
    delay(500);
    sensorValue = analogRead(sensorPin); 
 Serial.println("moisture value : ");
 Serial.println(sensorValue);
 
  
}
void pulse () // Interrupt function

{
  pulse_freq++;
}
