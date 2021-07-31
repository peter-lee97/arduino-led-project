// Importing libraries
#include <FastLED.h>

#define NUM_LEDS 8 // Define number of leds connected
#define LED_PIN_1 6 // Connect DI on LED to arduino pin

const int CURRENT_BRIGHTNESS = 16;
const int MAX_BRIGHTNESS = 64;
const int MIN_BRIGHTNESS = 2;

CRGB leds[NUM_LEDS]; // Declaring array of LEDs

void setup() {
  // Setup for LED
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds, NUM_LEDS);

  // Set brightness
  FastLED.setBrightness(CURRENT_BRIGHTNESS);

  // For debugging
  Serial.begin(9600);
  Serial.println("Setup");
}

void loop() {
  // LED Sequences, comment to hide/unhide functions
  blinkingLED();

  
//  loopLED1();
//  loopLED2();
//  breathingLED();
//  rainbowEffect(3000);
}

void blinkingLED() {
  // Toggling LED 0 ON & OFF
  leds[0] = CRGB::White; // Set color to White using standard color name
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Black; // Turn off
  FastLED.show();
  delay(200);
}

// Variant 1: Turn ON and OFF all LEDs
// Clockwise
void loopLED1() {
  // Loop through all LEDs in sequence
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = 0xFF44DD; // Set color using Hex value
    FastLED.show();
    delay(100);
  }
  clearLEDs();
}

// Variant 2: TURN ON and OFF all LEDs one at a time
// Counter clockwise
void loopLED2() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[(NUM_LEDS - i - 1)] = 0x658CBD;
    FastLED.show();
    delay(100);
    leds[(NUM_LEDS - i - 1)] = CRGB::Black;
    FastLED.show();
    delay(100);
  }
}

// Change brightness between MIN & MAX brightness
void breathingLED() {
  // Set all LEDs to color
  // Incrementing brightness
  fill_solid(leds, NUM_LEDS, 0xFFD454);
  for (int i = MIN_BRIGHTNESS; i < MAX_BRIGHTNESS; i++) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(33);
  }

  // Decrementing brightness
  for (int i = MAX_BRIGHTNESS; i >= MIN_BRIGHTNESS; i--) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(33);
  }
  clearLEDs();
}

// Rainbow effect with mix colors
void rainbowEffect(int duration) {
  // Run function for n seconds
  int gHue = 0;
  int i = 0;
  while (i < duration) {
    fill_rainbow(leds, NUM_LEDS, gHue, NUM_LEDS);
    FastLED.show();
    delay(20);
    gHue++;
    i = i + 20;
  }

}

void clearLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0, 0 , 0); // Set color by assigning individual RGB channel
    FastLED.show();
  }
}
