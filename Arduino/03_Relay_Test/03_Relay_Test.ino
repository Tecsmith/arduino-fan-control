
/*
  A. Select "Generic ESP8622 Module" board
  1. Output to serial (for debug)
  2. Blink I2C/Qwiic Relay, @see https://www.smart-prototyping.com/Zio-Qwiic-Relay
*/

#include <Wire.h>

#define SDA_PIN 0
#define SCL_PIN 2
// const int16_t I2C_MASTER = 0x07;
const int16_t I2C_RELAY = 0x18;


void setup() {
  Serial.begin(115200);

  while (!Serial);  // Leonardo: wait for serial monitor

  Serial.print("Starting... ");

  Wire.pins(SDA_PIN, SCL_PIN);
  Wire.begin();  // join i2c bus with sda = 0, scl = 2

  Serial.println();
}


void readFromSlave() {
  // if data size is available from nodes
}

// the loop function runs over and over again forever
void loop() {

  Wire.beginTransmission(I2C_RELAY);
  Wire.write(0x01);  // on
  Wire.endTransmission();

  delay(1000);

  // ***

  Wire.beginTransmission(I2C_RELAY);
  Wire.write(0x00);  // off
  Wire.endTransmission();

  delay(1000);

  Wire.beginTransmission(I2C_RELAY);
  Wire.write(0x04);
  Wire.endTransmission();

  delay(1);

  // ***

  Wire.requestFrom(I2C_RELAY, 2);

  int x = Wire.available();
  Serial.print(x);

  if (x >= 2) {
    int v_maj = Wire.read();
    int v_min = Wire.read();

    Serial.print("Version ");
    Serial.print(v_maj);
    Serial.print(".");
    Serial.print(v_min);
  }
}
