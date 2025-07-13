/*
 * ============================================================
 * Project: LED Matrix (Breath Effect)
 * Developer: Sean Conroy
 * Board: Arduino Mega or Mega 2560
 * License: MIT
 * Description:
 *   - Creates a smooth breathing (fade in/out) effect on a 12-LED WS2812 strip.
 *   - Uses HSV color space to maintain a fixed hue and saturation.
 *   - Brightness (value) is modulated with a sine wave for natural pulsing.
 *   - Adjustable hue, saturation, and breathing cycle duration.
 * ============================================================
 */

#include <Adafruit_NeoPixel.h>

#define LED_PIN     6
#define NUM_LEDS    12
#define BRIGHTNESS  150

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();
}

void loop() {
  breatheHSV(0, 255, 8000); 
}

void breatheHSV(uint16_t hue, uint8_t sat, uint16_t cycleTime) {
  static uint32_t startTime = millis();
  uint32_t now = millis();
  float progress = (now - startTime) % cycleTime;
  float phase = progress / (float)cycleTime * 2 * PI;

  // Generate brightness using sine wave (0–1)
  float brightness = (sin(phase - PI / 2) + 1.0) / 2.0;

  // Scale brightness to 0–255
  uint8_t value = (uint8_t)(brightness * 255);

  uint32_t color = strip.gamma32(strip.ColorHSV(hue, sat, value));

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }

  strip.show();
  delay(20);
}
