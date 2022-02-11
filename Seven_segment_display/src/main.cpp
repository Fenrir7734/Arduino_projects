#include <Arduino.h>

#define PIN_A 7
#define PIN_B 6
#define PIN_C 11
#define PIN_D 12
#define PIN_E 13
#define PIN_F 8
#define PIN_G 9
#define PIN_DP 10

#define BUTTON_PIN 2

#define WAIT_TIME 1000

uint8_t pins[] = {PIN_DP, PIN_G, PIN_F, PIN_E, PIN_D, PIN_C, PIN_B, PIN_A};
uint8_t numbers[] = {0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110};

volatile uint8_t i;
unsigned long timeStamp;
volatile bool buttonPressed = false;

void handleButton() {
    if (digitalRead(BUTTON_PIN) == 0) {
        buttonPressed = true;
    } else {
        buttonPressed = false;
        i = (uint8_t) random(10);
    }
}

void interruptibleDelay(unsigned long wait) {
    timeStamp = millis();
    while ((millis() - timeStamp) <= wait && !buttonPressed);
}

void clearDisplay() {
    for (uint8_t i = 0; i < 10; i++) {
        digitalWrite(pins[i], LOW);
    }
}

void loopDisplay() {
    for (uint8_t i = 2; i < 8; i++) {
        if (i == 2) {
            digitalWrite(pins[7], LOW);
        } else {
            digitalWrite(pins[i - 1], LOW);
        }
        digitalWrite(pins[i], HIGH);
        
        timeStamp = millis();
        while ((millis() - timeStamp <= 50));
    }
}

void setup() {
    for (uint8_t i = 0; i < 8; i++) {
        pinMode(pins[i], OUTPUT);
    }

    pinMode(BUTTON_PIN, INPUT);
    digitalWrite(BUTTON_PIN, HIGH);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButton, CHANGE);
}
 
void loop() {
    for (i = 0; i < 10; i++) {
        if (buttonPressed) {
            while (buttonPressed) {
                clearDisplay();
                loopDisplay();
            }
        } 
        
        uint8_t number = numbers[i];
        for (uint8_t j = 0; j < 8; j++) {
            digitalWrite(pins[j], number & (1 << j));
        }

        interruptibleDelay(WAIT_TIME);
    }
}