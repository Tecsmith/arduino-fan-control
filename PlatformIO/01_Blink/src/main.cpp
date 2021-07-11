#include <Arduino.h>

/** Blink
 * based on: https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
 */

static const uint8_t MY_LED_PIN = LED_BUILTIN;

// Remember that the ESP-01S does not have an LED.

void setup() {
  // put your setup code here, to run once:
  pinMode(MY_LED_PIN, OUTPUT);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(MY_LED_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(150);                   // wait for a 3/20 seconds
    digitalWrite(MY_LED_PIN, LOW);   // turn the LED off by making the voltage LOW
    delay(150);                   // wait for a 3/20 seconds
  }
  delay(800);                     // wait 4/5 seconds
}
