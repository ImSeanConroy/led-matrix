/*
 * ============================================================
 * Project: LED Matrix (Chaser Effect)
 * Developer: Sean Conroy
 * Board: Arduino Mega or Mega 2560
 * License: MIT
 * Description:
 *   - Implements a simple single-LED chaser effect on a 12-LED WS2812 strip.
 *   - Sequentially lights each LED in red, green, and blue colors.
 *   - Clears the strip between each step to create a moving dot effect.
 *   - Adjustable delay controls the speed of the chaser animation.
 * ============================================================
 */

#include <Adafruit_NeoPixel.h>

#define LED_PIN     6
#define NUM_LEDS    12
#define BRIGHTNESS  64

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();
}

void loop() {
  chaserEffect(strip.Color(255, 0, 0), 100);
  chaserEffect(strip.Color(0, 255, 0), 100);
  chaserEffect(strip.Color(0, 0, 255), 100);
}

void chaserEffect(uint32_t color, int delayTime) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.clear();
    strip.setPixelColor(i, color);
    strip.show();
    delay(delayTime);
  }
}
