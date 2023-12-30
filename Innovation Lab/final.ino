#include <SoftwareSerial.h>

SoftwareSerial bluetooth(1, 0); 


const int turbidityPin = A0;
int sensorPin = 2;
int sensorPin1 = 3;
int sensorPin2 = 4;
volatile long pulse;
volatile long pulse1;
volatile long pulse2;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);  
  bluetooth.begin(9600);  
  attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
  attachInterrupt(digitalPinToInterrupt(sensorPin1), increase1, RISING);
  attachInterrupt(digitalPinToInterrupt(sensorPin2), increase2, RISING);
}


void loop() {
  
  int turbidityValue = analogRead(turbidityPin);

  
  float turbidity = map(turbidityValue, 0, 1023, 0, 100); 

  
  Serial.print("turbidity: ");
  Serial.println(turbidity);

  
  bluetooth.print("turbidity: ");
  bluetooth.println(turbidity);
  Serial.println(pulse);
  Serial.println(pulse1);
  Serial.println(pulse2);

  if (pulse1 + pulse2 == pulse){
    bluetooth.println("no leakage detected: ");
  }
  else{
    bluetooth.println("leakage detected: ");
  }

 
  delay(10); 
}

void increase() {
  pulse++;
}

void increase1() {
  pulse1++;
}

void increase2() {
  pulse2++;
}