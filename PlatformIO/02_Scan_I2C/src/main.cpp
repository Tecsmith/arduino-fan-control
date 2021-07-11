#include <Arduino.h>
#include <Wire.h>  // include Wire.h library

/** Arduino I2C Scanner
 * Based on code by: Arbi Abdul Jabbaar
 * @see https://create.arduino.cc/projecthub/abdularbi17/how-to-scan-i2c-address-in-arduino-eaadda
 */

#ifdef ARDUINO_ESP8266_ESP01
  #define SDA_PIN 0
  #define SCL_PIN 2
#endif

void setup() {
  #ifdef ARDUINO_ESP8266_ESP01
  Wire.begin(SDA_PIN, SCL_PIN);
  #else
  Wire.begin();
  #endif
  Serial.begin(57600);  // the baudrate of serial monitor is default to 9600
  while (!Serial) delay(10);  // wait for serial monitor
  Serial.println("\nI2C Scanner\n-----------\n\n");
}

void loop() {
  byte error, address;  // variable for error and I2C address
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ ) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {

      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");

      nDevices++;

    } else if (error == 4) {

      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);

    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);  // wait 5 seconds for the next I2C scan
}
