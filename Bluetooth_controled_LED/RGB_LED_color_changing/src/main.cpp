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
uint8_t index = 0;

unsigned long pow(int a, int b) {
  unsigned long result = 1;

  for (int i = 0; i < b; i++) {
    result *= a;
  }
  return result;
}

unsigned long hexToDec(char* arr, uint8_t size) {
  unsigned long dec = 0;

  for (uint8_t i = 0; i < size; i++) {
    char curr = arr[size - i - 1];
    
    if (curr >= 48 && curr <= 57) {
      curr -= 48;
    } else if (curr >= 65 && curr <= 70) {
      curr = (curr - 65) + 10;
    } else if (curr >= 97 && curr <= 102) {
      curr = (curr - 97) + 10;
    }

    dec += (curr * pow(16, i));
  }

  return dec;
}

int normalizeColorValue(int value) {
  if (COMMON_ANODE) {
    return 255 - value;
  } else {
    return value;
  }
}

void setColor(char* hex) {
  unsigned long dec = hexToDec(hex, index);

  int red = (dec >> 16) & 0xFF;
  int green = (dec >> 8) & 0xFF;
  int blue = dec & 0xFF;

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
      setColor(hex);
    } else if (started && index < 6) {
      hex[index++] = (char) value;
    } else {
      HC06.flush();
    }
  }
}