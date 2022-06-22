#include <Arduino.h>
#include <SoftwareSerial.h>

#define COMMON_ANODE true
#define LED_RED_PIN 9
#define LED_GREEN_PIN 10
#define LED_BLUE_PIN 11

#define RX_PIN 2
#define TX_PIN 3

#define START_SIGN 60
#define END_SIGN 62

SoftwareSerial HC06(RX_PIN, TX_PIN);

uint8_t started = 1;
char hex[6];
int index = 0;

int normalizeColorValue(int value) {
  if (COMMON_ANODE) {
    return 255 - value;
  } else {
    return value;
  }
}

void setColor() {
  int red, green, blue;

  // It should be replaced by something cheaper
  sscanf(hex, "%02x%02x%02x", &red, &green, &blue);

  analogWrite(LED_RED_PIN, normalizeColorValue(red));
  analogWrite(LED_GREEN_PIN, normalizeColorValue(green));
  analogWrite(LED_BLUE_PIN, normalizeColorValue(blue));
}

void setup() {
  HC06.begin(9600);
}

void loop() {
  while (HC06.available() > 0) {
    int value = HC06.read();

    if (value == START_SIGN) {
      started = 1;
      index = 0;
    } else if (value == END_SIGN) {
      started = 0;
      setColor();
    } else if (started && index < 6) {
      hex[index++] = (char) value;
    } else {
      HC06.flush();
    }
  }
}