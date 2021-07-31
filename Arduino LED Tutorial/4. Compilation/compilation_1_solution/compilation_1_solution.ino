// Importing libraries
#include <FastLED.h>

// Defining values
#define TRIG_PIN 3
#define ECHO_PIN 2
#define LED_PIN_1   6
#define NUM_LEDS    8
#define DARK_GREEN 0x66FFCC

const int triggerDistance = 20;
const int MAX_BRIGHTNESS = 64;
const int MIN_BRIGHTNESS = 2;
const int BRIGHTNESS = 32;

int currentDistance;
long duration;

CRGB leds1[NUM_LEDS];


void setup() {
  // Setup for LEDs
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds1, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  clearLEDs();

  // Setup for Ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // For debugging
  Serial.begin(9600);
  Serial.println("Initialize");
}


void loop() {
  // Reading values from Ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  digitalWrite(ECHO_PIN, INPUT);
  duration = pulseIn(ECHO_PIN, HIGH);

  currentDistance = uSecondsToCM(duration);
  delay(100);


  if (currentDistance <= triggerDistance) {
    Serial.print("Distance: ");
    Serial.println(currentDistance);
    triggered();
  }
}

// Sequence to execute when triggered
// Add additional sequence
void triggered() {
  clearLEDs();

  // Run Ring loop
  ringLoop();
  // Run Breathing light
  breathingLight();
  // Run DIM Light
  dimLED(1000);

  // End Sequence
  Serial.println("End Sequence");
}

void clearLEDs() {
  for (int i = 0; i <= NUM_LEDS; i++) {
    leds1[i] = CRGB (0, 0, 0);
  }
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
}

// Function to convert microseconds to cm
long uSecondsToCM(long uSeconds) {
  return uSeconds / 29 / 2;
}

// Loop through LEDs with acceleration
void ringLoop() {
  // Initial delay
  float delayDuration = 400;
  float totalDuration = delayDuration;

  while ( delayDuration > 1) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds1[i] = DARK_GREEN;
      // Decides which led to start with
      fadeToBlackBy(leds1, NUM_LEDS, 90);

      FastLED.show();
      delay(delayDuration);
    }

    // Reduce delay Duration
    delayDuration = delayDuration * 0.8;

    // Calculate total duration
    totalDuration = totalDuration + delayDuration * NUM_LEDS;
  }
  Serial.print("Time taken: ");
  Serial.println(totalDuration, 2);
  Serial.println("Exit ringLoop()");
}

// LED brightness change from MAX_BRIGHTNESS to MIN_BRIGHTNESS
void breathingLight() {

  int repeatTimes = 5;
  float totalDuration = 0;
  int ledDelay = 33;
  int d = 0;
  while (d < repeatTimes) {
    fill_solid(leds1, NUM_LEDS, DARK_GREEN);

    for (int i = MIN_BRIGHTNESS; i < MAX_BRIGHTNESS ; i++) {
      FastLED.setBrightness(i);
      FastLED.show();
      delay(ledDelay);
    }
    for (int i = MAX_BRIGHTNESS; i > MIN_BRIGHTNESS ; i--) {
      FastLED.setBrightness(i);
      FastLED.show();
      delay(ledDelay);
    }

    totalDuration = totalDuration + (MAX_BRIGHTNESS - MIN_BRIGHTNESS) * ledDelay;
    d = d + 1;
    delay(1);
  }
  Serial.print("Time taken: ");
  Serial.println(totalDuration, 2);
  Serial.println("Exit beathingLight()");
}

// Dim LED with given timing
void dimLED(float timing) {
  // Decrease brightness
  float lightStep = MAX_BRIGHTNESS / timing;
  int currentBrightness = MAX_BRIGHTNESS;

  // For debug
  Serial.print("Light Step: ");
  Serial.println(lightStep);

  while (currentBrightness > 0) {
    fill_solid(leds1, NUM_LEDS, DARK_GREEN);
    FastLED.setBrightness(currentBrightness);
    FastLED.show();
    // Reduce brightness level
    currentBrightness = currentBrightness - lightStep;

    Serial.println(currentBrightness);
    delay(33);
  }
  clearLEDs();
}
