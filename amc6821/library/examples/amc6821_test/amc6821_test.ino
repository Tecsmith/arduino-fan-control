
#include <Blink.h>
// #include <I2C.h>  // http://dsscircuits.com/articles/arduino-i2c-master-library.html
#include <Wire.h>
#include "AMC6821.h"

void setup() {
  Serial.begin(9600);
  Serial.println("*** ---------- begin");

  /* ----- */

  // I2c.begin();
  // I2c.scan();

  Wire.begin();
  amc6821.reset();
  delay(2000);
//  amc6821.start();
//  amc6821.setPWMInvert();  // Dell fan

//  amc6821.setTachMode();


  /* Software-RPM Mode */  /*
  amc6821.setTachFast();
  amc6821.setMode(mode_software_rpm);
  amc6821.setRPM(tach_setting, 1000);
  /* */

  /* Software-DCY Mode */  /*
  amc6821.setMode(mode_software_dcy);
  amc6821.setDCY(63);
  /* */

  /* Auto Temperature Mode */
//  amc6821.setMode(mode_auto_remote);
  
  /* ===== */
}

unsigned long m = 0;

void loop() {
  Blink.loop(true);

  unsigned long n = millis();
  if ((m + 5000) > n) return;
  m = n;

  int x;
  
  /*
  x = amc6821.readTemp(local_temp);
  Serial.print("Local temp = ");
  Serial.print(x);
  x = amc6821.readTemp(local_temp_8ths) * 125;
  Serial.print(".");
  Serial.print(x);
  Serial.println();


  x = amc6821.readTemp(remote_temp);
  Serial.print("Remote temp = ");
  Serial.print(x);
  x = amc6821.readTemp(remote_temp_8ths) * 125;
  Serial.print(".");
  Serial.print(x);
  Serial.println();

  x = amc6821.readDCY();
  Serial.print("DCY = ");
  Serial.print(x);
  Serial.println();


  x = amc6821.readSpeed(tach_setting);
  Serial.print("Tach Setting = ");
  Serial.print(x);
  Serial.println();

  x = amc6821.readRPM(tach_setting);
  Serial.print("RPM Setting = ");
  Serial.print(x);
  Serial.println();

  x = amc6821.readSpeed(tach_data);
  Serial.print("Tach = ");
  Serial.print(x);
  Serial.println();

  x = amc6821.readRPM(tach_data);
  Serial.print("RPM = ");
  Serial.print(x);
  Serial.println();

  Serial.println();
  /* ----- */

  /*
  Wire.beginTransmission(0x4D);
  Wire.write(0x0B);
  Wire.endTransmission();

  Wire.requestFrom(0x4D, 1);
  if (Wire.available()) {
    byte b = Wire.read();
    Serial.print("0x");
    Serial.print(b, HEX);
    Serial.print(" ");
    Serial.println(b);
  }
  */
  /* ===== */
}
