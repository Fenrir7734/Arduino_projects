#include <FastLED.h>

#define LED_DATA_PIN 13
#define MICROPHONE_PIN A5
#define LED_NUM 8
#define LED_MAX 255 * LED_NUM

CRGB leds[LED_NUM];

void clearLeds() {
  for (int i = 0; i < LED_NUM; i++) {
    leds[i].setRGB(0, 0, 0);
  }
}

void setLeds(int level) {
  for (int i = 0; i < LED_NUM; i++) {
    if (level >= 255) {
      leds[i] = CRGB(0, 0, 255);
      level -= 255;
    } else if (level > 0 && level < 255) {
      leds[i] = CRGB(0, 0, level);
      level -= 255;
    } else {
      leds[i] = CRGB(0, 0, 0);
    }
  }
}

void setup() {
  FastLED.addLeds<WS2812 ,LED_DATA_PIN, GRB>(leds, LED_NUM);
}

void loop() {
  int read = analogRead(MICROPHONE_PIN);
  int level = (2048. / 500.) * read;

  if (level != 0) {
    setLeds(level);
  } else {
    clearLeds();
  }

  FastLED.show();
}