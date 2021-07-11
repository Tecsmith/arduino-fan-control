#include <Arduino.h>

/** Qwiic Relay
 * (c) Kevin Kuwata @ SparkX
 *
 * @see: https://www.sparkfun.com/products/15093
 *   <or>
 * @see: https://www.smart-prototyping.com/Zio-Qwiic-Relay
 */

#include <Wire.h>
#define COMMAND_RELAY_OFF      0x00
#define COMMAND_RELAY_ON       0x01
#define COMMAND_CHANGE_ADDRESS 0x03

// const byte qwiicRelayAddress = 0x18;     // Default Address
const byte qwiicRelayAddress = 0x19;     // Secondary Address

// RelayOn() turns on the relay at the qwiicRelayAddress
// Checks to see if a slave is connected and prints a
// message to the Serial Monitor if no slave found.
void relayOn() {
  Wire.beginTransmission(qwiicRelayAddress);
  Wire.write(COMMAND_RELAY_ON);
  Wire.endTransmission();
}

// RelayOff() turns off the relay at the qwiicRelayAddress
// Checks to see if a slave is connected and prints a
// message to the Serial Monitor if no slave found.
void relayOff() {
  Wire.beginTransmission(qwiicRelayAddress);
  Wire.write(COMMAND_RELAY_OFF);
  Wire.endTransmission();
}

/*
 * testForConnectivity() checks for an ACK from an Relay.
 * If no ACK program freezes and notifies user.
 */
void testForConnectivity() {
  Wire.beginTransmission(qwiicRelayAddress);
  //check here for an ACK from the slave, if no ack don't allow change?
  if (Wire.endTransmission() != 0) {
    Serial.println("Check Connections. No slave attached.");
    while (1);
  }
}

/**
 * changeAddress() takes a 7 bit I2C Address
 * and writes it to the Relay. This function
 * checks to see if the address is between
 * 0x07 and 0x78. If valid, the new address is
 * saved to the Relay's EEPROM. If not valid
 * address is not changed and is ignored.
 * This function returns true if successful and
 * false if unsuccessful.
 */
boolean changeAddress(uint8_t newAddress) {
  Wire.beginTransmission(qwiicRelayAddress);
  // check here for an ACK from the slave
  if (Wire.endTransmission()  != 0) {
    Serial.println("Check Connections. No slave found.");
    return (false);
  }

  // check if valid newAddress.
  if (newAddress < 0x07 || newAddress > 0x78) {
    Serial.println("Invalid I2C address");
    return (false);
  }
  // valid newAddress
  Wire.beginTransmission(qwiicRelayAddress);
  Wire.write(COMMAND_CHANGE_ADDRESS);
  Wire.write( newAddress );
  Wire.endTransmission();
  return (true); // Success!
}

/**
 * setup()
 */
void setup() {
  Serial.begin(9600);
  Serial.println("Qwiic Relay Examples");
  Wire.begin();  // join the I2C Bus

  testForConnectivity();
}

/**
 * loop()
 */
void loop() {

  // change the I2C address to 0x19
  if (false) {
    byte error = changeAddress(0x19);  // Change the Relay's address to 0x19
    if (error != true) {
      Serial.println("Error");
    } else {
      Serial.println("Success");
    }
    while (1);
  }

  // loop on and off in 10 sec intervals
  if (true) {
    relayOn();
    Serial.println("Relay is On.");
    delay(10000);
    relayOff();
    Serial.println("Relay is Off.");
    delay(10000);
  }
}
