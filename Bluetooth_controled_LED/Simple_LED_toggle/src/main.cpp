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
  if (bluetoothSerial.available()) {              // Check if something was send
    byte receivedData = bluetoothSerial.read();   // Read it

    if (receivedData == 48) {                     // ASCII code for "0"
      digitalWrite(LED_PIN, LOW);                 // Turn off LED
    } else if (receivedData == 49) {              // ASCII code for "1"
      digitalWrite(LED_PIN, HIGH);                // Turn on LED
    }
  }
  delay(200);
}