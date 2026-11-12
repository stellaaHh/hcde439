// Load the library for the foil sensor.
#include <CapacitiveSensor.h>

// Send on D2 and read the foil on D4.
CapacitiveSensor touchPad(2, 4);

// Use D5 to drive the MOSFET gate.
const int stripPin = 5;

// Use 1000 as the cutoff for a touch.
const long touchThreshold = 1000;

// Set the PWM value for the dim setting.
const int dimLevel = 40;

// Set the PWM value for the bright setting.
const int brightLevel = 200;

// Set up the output and Serial Monitor.
void setup() {
  // Set the output latch LOW before enabling the output.
  digitalWrite(stripPin, LOW);

  // Make D5 an output so it drives the gate LOW.
  pinMode(stripPin, OUTPUT);

  // Send readings to the Serial Monitor at 9600 baud.
  Serial.begin(9600);
}

// Read the foil and update the strip.
void loop() {
  // Take 30 samples for one reading.
  long reading = touchPad.capacitiveSensor(30);

  // Print the reading to check the threshold.
  Serial.println(reading);

  // Check for a sensor error.
  if (reading < 0) {
    // Turn off the strip.
    analogWrite(stripPin, 0);
  }
  // Check whether the reading reaches the touch threshold.
  else if (reading >= touchThreshold) {
    // Use the bright setting.
    analogWrite(stripPin, brightLevel);
  }
  // Handle valid readings below the threshold.
  else {
    // Use the dim setting.
    analogWrite(stripPin, dimLevel);
  }

  // Wait 20 ms before reading again.
  delay(20);
}