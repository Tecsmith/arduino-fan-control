// --------------------------------------
// Modified from: http://playground.arduino.cc/Main/I2cScanner
// i2c_scanner

#include <Wire.h>

#define SDA_PIN 0
#define SCL_PIN 2

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.begin(57600);
  while (!Serial);  // Leonardo: wait for serial monitor
  Serial.println("I2C Scanner (ESP-01)");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println();  Serial.println();
  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address <= 127; address++ ) {

    // delay(1);

    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {

      nDevices++;

      Serial.print("[");
      Serial.print(nDevices);
      Serial.print("] Address = ");
      Serial.print(address, DEC);
      Serial.print(" (0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(")");


    } else if (error == 4) {

      Serial.print("Error @ (0x");
      if (address<16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(")");

    }
  }

  if (nDevices == 0)
    Serial.println("No I2C devices found.");
  else {
      Serial.print("Found ");
      Serial.print(nDevices);
      Serial.print(" I2C device");
      if (nDevices > 1) Serial.print("s");
      Serial.println(".");
  }

  delay(10000);  // wait 5 seconds for next scan
}
