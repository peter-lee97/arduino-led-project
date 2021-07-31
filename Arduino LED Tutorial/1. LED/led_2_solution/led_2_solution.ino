/*
   Declare the LEDs with an unique name
   Choose 3 pins from 2 ~ 13
*/
int led_1 = 7;
int led_2 = 6;
int led_3 = 5;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // Iterate number of LEDs (0, 1, 2)
  for (int i = 0; i <= 2; i++) {
    if (i == 0) {
      digitalWrite(led_1, HIGH);   
      delay(1000);               
      digitalWrite(led_1, LOW);   
      delay(1000);              
    }
    if ( i == 1) {
      digitalWrite(led_2, HIGH);  
      delay(1000);               
      digitalWrite(led_2, LOW);  
      delay(1000);
    }
    if (i == 2) {
      digitalWrite(led_3, HIGH);
      delay(1000);
      digitalWrite(led_3, LOW);
      delay(1000);
    }
  }
}
