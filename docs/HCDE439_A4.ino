// Load the library that reads the capacitive touch pad.
#include <CapacitiveSensor.h>

// Load the library that controls the servo.
#include <Servo.h>

// Use D2 as the send pin and D4 as the receive pin.
CapacitiveSensor touchPad(2, 4);

// Create an object to control the servo arm.
Servo arm;

// Use 30 samples per reading, following the class demo.
const int sampleCount = 30;

// Separate untouched readings around 100 from touched readings around 5500.
const long touchThreshold = 1000;

// Use 0 degrees for the startup and released positions.
const int releasedAngle = 0;

// Move to 150 degrees when the foil is touched.
const int touchedAngle = 150;

// Set up the sensor and return the servo to its starting position.
void setup() {
  // Disable periodic baseline recalibration during the demo.
  touchPad.set_CS_AutocaL_Millis(0xFFFFFFFF);

  // Send the servo control signal on D9.
  arm.attach(9);

  // Command the servo to move to its starting position.
  arm.write(releasedAngle);

  // Give the servo one second to move before reading the sensor.
  delay(1000);

  // Start Serial Monitor output at 9600 baud.
  Serial.begin(9600);
}

// Read the touch pad and update the servo position repeatedly.
void loop() {
  // Measure the touch pad using the selected sample count.
  long reading = touchPad.capacitiveSensor(sampleCount);

  // Print the reading so I can check the threshold.
  Serial.println(reading);

  // Leave the servo in place if the library reports a negative error value.
  if (reading >= 0) {
    // Check whether the reading is high enough to count as a touch.
    if (reading >= touchThreshold) {
      // Move the servo to the touched position.
      arm.write(touchedAngle);
    }
    // Use the released position when the reading is below the threshold.
    else {
      // Return the servo to its starting position.
      arm.write(releasedAngle);
    }
  }

  // Pause briefly before starting the next measurement.
  delay(20);
}