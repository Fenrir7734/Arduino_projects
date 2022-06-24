#include <Arduino.h>
#include <SoftwareSerial.h>

#define COMMON_ANODE true                                  // true - common anode RGB LED, false - common cathode RGB LED 
#define LED_RED_PIN 9
#define LED_GREEN_PIN 10
#define LED_BLUE_PIN 11

#define RX_PIN 2
#define TX_PIN 3

#define START_SIGN 60                                      // ASCII code of begin delimeter
#define END_SIGN 62                                        // ASCII code of end delimeter

SoftwareSerial HC06(RX_PIN, TX_PIN);

uint8_t started = 1;
char hex[6];
uint8_t index = 0;

// Function for finding the power of a given number.
//
// params:
//    a       base
//    b       exponent, for correct result it should be a positive integer
// return:
//    number a raised to the power of b
unsigned long pow(int a, int b) {
  unsigned long result = 1;

  for (int i = 0; i < b; i++) {
    result *= a;
  }
  return result;
}

// Function for changing hexadecimal number to its decimal equivalent.
// 
// params:
//    arr     array of chars containing representation of hexadecimal number
//    size    size of array
// return:
//    decimal equivalent of given hexadecimal number
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

// Function that changes (or not) value of RGB parameter depending on type of LED.
//
// params:
//    value   value of RGB parameter
// return:
//    RGB parameter value adjusted to the type of LED  
int normalizeColorValue(int value) {
  if (COMMON_ANODE) {
    return 255 - value;
  } else {
    return value;
  }
}

// Function that sets color of LED.
//
// params:
//    hex    hexadecimal representation of RGB code
void setColor(char* hex) {
  unsigned long dec = hexToDec(hex, index);

  int red = (dec >> 16) & 0xFF;                            // extract red parameter from RGB code
  int green = (dec >> 8) & 0xFF;                           // extract green parameter from RGB code
  int blue = dec & 0xFF;                                   // extract blue parameter from RGB code

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