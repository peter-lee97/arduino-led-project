/*
   Declare the LEDs with an unique name
   Choose 3 pins from 2 ~ 13
*/
int led_1 = 7;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led_1, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // Iterate number of LEDs
  digitalWrite(led_1, HIGH);
  delay(1000);
  digitalWrite(led_1, LOW);
  delay(1000);
}
