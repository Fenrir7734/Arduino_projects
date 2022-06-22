#include <Arduino.h>
#include <SoftwareSerial.h>

#define LED_PIN 13

#define RX_PIN 2
#define TX_PIN 3

SoftwareSerial bluetoothSerial(RX_PIN, TX_PIN);

void setup() {
  pinMode(LED_PIN, OUTPUT);
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
