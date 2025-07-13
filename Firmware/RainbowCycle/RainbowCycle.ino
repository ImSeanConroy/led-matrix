/*
 * ============================================================
 * Project: LED Matrix (Rainbow Cycle)
 * Developer: Sean Conroy
 * Board: Arduino Mega or Mega 2560
 * License: MIT
 * Description:
 *   - Creates a smooth, continuous rainbow animation across a 12-LED WS2812 strip.
 *   - Uses HSV color space to evenly distribute hues across the LEDs.
 *   - Cycles hues over time for a dynamic color shifting effect.
 *   - Adjustable brightness and animation speed.
 * ============================================================
 */

#include <Adafruit_NeoPixel.h>

#define LED_PIN     6
#define NUM_LEDS    12
#define BRIGHTNESS  120

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();
}

void loop() {
  rainbowHSV(30);
}

void rainbowHSV(uint8_t wait) {
  static uint16_t startHue = 0;

  for (int i = 0; i < strip.numPixels(); i++) {
    // Spread hue evenly across strip
    uint16_t hue = startHue + (i * 65536L / strip.numPixels());

    // HSV: hue (0–65535), sat (0–255), value (0–255)
    uint32_t color = strip.gamma32(strip.ColorHSV(hue, 255, 255));  

    strip.setPixelColor(i, color);
  }

  strip.show();
  delay(wait);
  startHue += 256;
}
