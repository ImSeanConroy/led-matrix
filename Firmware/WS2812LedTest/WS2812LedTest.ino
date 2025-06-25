#include <Adafruit_NeoPixel.h>

#define LED_PIN     6
#define NUM_LEDS    3

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  delay(500);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    // Red Test
    setSingleLED(i, 255, 0, 0);
    delay(500);
    
    // Green Test
    setSingleLED(i, 0, 255, 0);
    delay(500);
    
    // Blue Test
    setSingleLED(i, 0, 0, 255);
    delay(500);
    
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
