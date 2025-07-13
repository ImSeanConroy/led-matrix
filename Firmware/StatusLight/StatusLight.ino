/*
 * ============================================================
 * Project: LED Matrix (Status Light)
 * Developer: Sean Conroy
 * Board: Arduino Mega or Mega 2560
 * License: MIT
 * Description:
 *   - Cycles through multiple color themes.
 *   - Displays smooth color gradients across a 12-LED WS2812 strip.
 *   - Each theme highlights a specific hue range (e.g., red-orange, blue, purple).
 *   - Automatically switches themes every 5 seconds with animated shifting colors.
 * ============================================================
 */

#include <Adafruit_NeoPixel.h>

#define LED_PIN     6
#define NUM_LEDS    12
#define BRIGHTNESS  64
#define COLOR_CYCLE_INTERVAL 5000

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

struct HueRange {
  const char* name;
  uint16_t hueMin;
  uint16_t hueMax;
};

HueRange themes[] = {
  { "Red",          12000, 25000 },
  { "Green",        0,     15000 },
  { "Blue",         45000, 55000 },
  { "Light Blue",   50000, 60000 },
  { "Purple",       30000, 40000 }
};

const uint8_t NUM_THEMES = sizeof(themes) / sizeof(themes[0]);
uint8_t currentTheme = 0;

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();
}

void loop() {
  static uint32_t lastSwitchTime = 0;
  static uint16_t startHue = 0;
  uint32_t now = millis();

  if (now - lastSwitchTime > COLOR_CYCLE_INTERVAL) {
    currentTheme = (currentTheme + 1) % NUM_THEMES;
    lastSwitchTime = now;
  }

  drawHSVTheme(startHue, 150);
  startHue += 256;
}

void drawHSVTheme(uint16_t startHue, uint8_t wait) {
  HueRange theme = themes[currentTheme];
  uint16_t hueRange = theme.hueMax - theme.hueMin;

  for (int i = 0; i < strip.numPixels(); i++) {
    uint16_t hue = theme.hueMin + ((startHue + i * 1000) % hueRange);
    uint32_t color = strip.gamma32(strip.ColorHSV(hue, 255, 255));
    strip.setPixelColor(i, color);
  }

  strip.show();
  delay(wait);
}

