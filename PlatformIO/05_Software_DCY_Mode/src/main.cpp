#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Tecsmith_AMC6821.h>

#ifdef ARDUINO_ESP8266_ESP01
  #define SDA_PIN 0
  #define SCL_PIN 2
#endif

/**
 * ## Software DCY Control Mode
 *
 * When the bits [FDRC1:FDRC0] = [00], the fan works in the software DCY
 * control mode. The host writes the desired duty cycle value corresponding
 * to the required RPM into the DCY register. The duty cycle changes to the
 * new value immediately after the writing. In this mode, if the TACH
 * measurement is enabled (bit 2 of 0x01 = 1) and the TACH-MODE bit (bit 1 of
 * 0x01) is cleared ('0'), the duty cycle from the PWM-OUT pin is forced to 0%
 * when the value in the DCY register is less than 7%. However, if the TACH
 * measurement is disabled (bit 2 of 0x01 is cleared) or the TACH mode is set
 * ('1'), the DCY register always keeps the programmed value written by the
 * host and is not forced to '0' even when the programmed value is less than
 * 7%.
*/

Tecsmith_AMC6821 amc6821;  // instance
String command;  // interact with Serial

void __b(uint8_t addr, const char * pre = "") {
  Serial.print(pre);  Serial.print(" ");
  uint8_t v = amc6821.read(addr);
  for (int x = 7; x >= 0; x--) { Serial.print(bitRead(v, x)); }
  Serial.print(" 0x");
  if (v < 16) { Serial.print("0"); }  Serial.println(v, 16);
}

void showPrompt() {
  Serial.println();
  __b(AMC6821_REG_CONF1, "c1");
  __b(AMC6821_REG_CONF2, "c2");
  __b(AMC6821_REG_CONF3, "c3");
  __b(AMC6821_REG_CONF4, "c4");
  __b(AMC6821_REG_STAT1, "s1");
  __b(AMC6821_REG_STAT2, "s2");
  __b(AMC6821_REG_DCY, "dc");
  Serial.println("\nType Command (hello, local, remote, show, 10 .. 100, help)");
  Serial.print("> ");
}

void showHelp() {
  Serial.println("\nCommands available:\n");
  Serial.println("  hello / H  - prints \"Hello World\" (used for testing serial interface)");
  Serial.println("  local / L  - show local temperature");
  Serial.println("  remote / R - show remote temperature");
  Serial.println("  show / S   - show duty cycel");
  Serial.println("  0          - 0% duty cycle");
  Serial.println("  10 / 1     - 10% duty cycle");
  Serial.println("  20 / 2     - 20% duty cycle");
  Serial.println("  30 / 3     - 30% duty cycle");
  Serial.println("  40 / 4     - 40% duty cycle");
  Serial.println("  50 / 5     - 50% duty cycle");
  Serial.println("  60 / 6     - 60% duty cycle");
  Serial.println("  70 / 7     - 70% duty cycle");
  Serial.println("  80 / 8     - 80% duty cycle");
  Serial.println("  90 / 9     - 90% duty cycle");
  Serial.println("  full / F   - 100% duty cycle");
  // Serial.println("");
  // Serial.println("");
}

void _setDCY(unsigned int percentage) {
  int p = amc6821.getDutyCycleP();
  Serial.print("Duty Cycle was ");
  Serial.print(p);
  Serial.println("%");

  amc6821.setDutyCycleP(percentage);
  Serial.print("Duty Cycle setting to ");
  Serial.print( percentage );
  Serial.println("%");

  delay(500);

  p = amc6821.getDutyCycleP();
  Serial.print("Duty Cycle is now at ");
  Serial.print(p);
  Serial.println("%");
}

// ---------- ! ----------

void setup() {
  // put your setup code here, to run once:

  Serial.begin(57600);
  while (!Serial) delay(10);

  #ifdef ARDUINO_ESP8266_ESP01
  Wire.begin(SDA_PIN, SCL_PIN);
  #else
  Wire.begin();
  #endif

  Serial.println("\n\n--------------------------------------------");
  Serial.println("Tecsmith_AMC6821 - Software DCY mode example");
  Serial.println("--------------------------------------------\n");

  // Try to initialize!
  if (!amc6821.begin( AMC6821_CONF1_FDRC_SOFTWARE_DCY )) {
    Serial.println("Failed to find AMC6821 chip");
    while (1) { delay(10); }
  }
  // amc6821.setDutyCycle(191);  // 75% DYC
  amc6821.setTachMode(false);
  amc6821.setPWMOutEnable(true);
  Serial.println("AMC6821 Found!");

  delay(2000);  // pause a bit

  Serial.print( amc6821.getFanControlMode() );

  amc6821.start();

  showPrompt();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();

    if (command.equals("h") || command.equals("hello")) {
      Serial.println("Hello World");
    }

    else if (command.equals("?") || command.equals("help")) {
      showHelp();
    }

    else if (command.equals("l") || command.equals("local")) {
      float t = amc6821.getLocalMilliTemp() / 1000;
      Serial.print("Local temp = ");
      Serial.print( t );
      Serial.print("°C / ");
      Serial.print( Tecsmith_AMC6821::toFahrenheit(t) );
      Serial.println("°F");
    }

    else if (command.equals("r") || command.equals("remote")) {
      float t = amc6821.getRemoteMilliTemp() / 1000;
      Serial.print("Remote temp = ");
      Serial.print( t );
      Serial.print("°C / ");
      Serial.print( Tecsmith_AMC6821::toFahrenheit(t) );
      Serial.println("°F");
    }

    else if (command.equals("s") || command.equals("show")) {
      int p = amc6821.getDutyCycleP();
      Serial.print("Duty Cycle is ");
      Serial.print(p);
      Serial.println("%");
    }

    else if (command.equals("0")) { _setDCY(0); }
    else if (command.equals("1") || command.equals("10")) { _setDCY(10); }
    else if (command.equals("2") || command.equals("20")) { _setDCY(20); }
    else if (command.equals("3") || command.equals("30")) { _setDCY(30); }
    else if (command.equals("4") || command.equals("40")) { _setDCY(40); }
    else if (command.equals("5") || command.equals("50")) { _setDCY(50); }
    else if (command.equals("6") || command.equals("60")) { _setDCY(60); }
    else if (command.equals("7") || command.equals("70")) { _setDCY(70); }
    else if (command.equals("8") || command.equals("80")) { _setDCY(80); }
    else if (command.equals("9") || command.equals("90")) { _setDCY(90); }
    else if (command.equals("f") || command.equals("full") || command.equals("100")) { _setDCY(100); }

    else if (command.equals("q") || command.equals("quit") || command.equals("bye")) {
      Serial.println("Can't quit, I'm an MCU");
    }
    else {
      Serial.print("Unknown command: ");
      command.toUpperCase();
      Serial.println(command);
    }

    showPrompt();
  }
  delay(1);
}
