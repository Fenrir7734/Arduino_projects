#include <Arduino.h>
#include <SoftwareSerial.h>

#define LED_PIN 13

SoftwareSerial bluetoothSerial(2, 3);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
}

void loop() {
  if (bluetoothSerial.available()) {
    byte receivedData = bluetoothSerial.read();

    if (receivedData == 48) {
      digitalWrite(LED_PIN, LOW);
    } else if (receivedData == 49) {
      digitalWrite(LED_PIN, HIGH);
    }
  }
  delay(200);
}