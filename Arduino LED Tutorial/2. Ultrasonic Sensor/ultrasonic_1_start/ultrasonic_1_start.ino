#define TRIG_PIN 3
#define ECHO_PIN 2

// Global Variable
long duration;
int currentDistanceCM;

// Constants
const int triggerDistance = 20; // Min. distance to trigger

void setup() {
  // Setup for Ultrasonic Sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // For Debugging, Serial Monitor
  Serial.begin(9600);
  Serial.println("Instantiated");
}

void loop() {
  // Reading from Ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  digitalWrite(ECHO_PIN, INPUT);
  duration = pulseIn(ECHO_PIN, HIGH);

  currentDistanceCM = uSecondsToCM(duration);
  delay(100);

  if (/*Replace with a conditional statement to show distance < triggerDistance */) {
    Serial.print("Distance: ");
    Serial.println(currentDistanceCM);
    delay(100);
  }
}

// Calculate Distance with Time
long uSecondsToCM(long uSeconds) {
  // Return an estimation of distance
  return uSeconds / 29 / 2;
}
