// Lab 4 code
const int trigPin = 8;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;
const double R1 = 0.0343/2;
const double R2 = R1/2.54;
const int threshold = 3;
//const int ledPin = 2;
//const int ledPin2 = 6;

// Lab 5 new code
#include <ArduinoBLE.h>

BLEService newService("170A"); // creating the service
BLEByteCharacteristic readChar("2A53", BLERead);
BLEByteCharacteristic writeChar("2A54", BLEWrite);

void setup() {
  // put your setup code here, to run once:
  // Lab 4 code
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
//  pinMode(ledPin, OUTPUT);
//  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);

  // Lab 5 new code
  while(!Serial);
  if (!BLE.begin()){
    Serial.println("Waiting for ArduinoBLE");
    while(1);
  }
  BLE.setDeviceName("JJ_Richard");
  BLE.setAdvertisedService(newService);
  newService.addCharacteristic(readChar);
  newService.addCharacteristic(writeChar);
  BLE.addService(newService);
  readChar.writeValue(0);
  writeChar.writeValue(0);
  BLE.advertise();
  Serial.println("Bluetooth device active");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Lab 4 code
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 
  distanceCm = duration * R1;
  distanceInch = duration * R2;
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.print(" cm/");
  Serial.print(distanceInch);
  Serial.println(" in");
  delay(1000);

//  if (distanceInch < threshold) {
//    digitalWrite(ledPin, HIGH);
//    digitalWrite(ledPin2, LOW);
//  }
//  else {
//    digitalWrite(ledPin, LOW);
//    digitalWrite(ledPin2, HIGH);
//  }

  // Lab 5 new code
  readChar.writeValue(distanceCm);
  if (writeChar.written()) {
    if (writeChar.value()) {

    }
    }
}
