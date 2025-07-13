/*
 * ============================================================
 * Project: LED Matrix (WS2812 LED Tester)
 * Developer: Sean Conroy
 * Board: Arduino Mega or Mega 2560
 * License: MIT
 * Description:
 *   - Sequentially tests each WS2812 LED in the strip.
 *   - Lights each LED in red, green, and blue for 300ms.
 *   - Turns off the LED briefly before moving to the next.
 *   - Helps verify LED functionality and color accuracy on a 12-LED strip.
 * ============================================================
 */

#include <Adafruit_NeoPixel.h>

#define LED_PIN     6
#define NUM_LEDS    12

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  delay(300);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    // Red Test
    setSingleLED(i, 255, 0, 0);
    delay(300);
    
    // Green Test
    setSingleLED(i, 0, 255, 0);
    delay(300);
    
    // Blue Test
    setSingleLED(i, 0, 0, 255);
    delay(300);
    
    // Turn off
    setSingleLED(i, 0, 0, 0);
    delay(300);
  }
}

void setSingleLED(int index, uint8_t r, uint8_t g, uint8_t b) {
  strip.clear();
  strip.setPixelColor(index, strip.Color(r, g, b));
  strip.show();
}
