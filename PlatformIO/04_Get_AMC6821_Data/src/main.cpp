#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Tecsmith_AMC6821.h>

#ifdef ARDUINO_ESP8266_ESP01
  #define SDA_PIN 0
  #define SCL_PIN 2
#endif

Tecsmith_AMC6821 amc6821;  // instance
byte looplimit;

void phex(int unsigned num, int precision = 2) {
  uint8_t b;
  char tmp[4];

  if ((precision != 2) && (precision != 4)) return;

  if (precision == 4) {
    b = (uint8_t)((num & 0xFF00) >> 8);
    sprintf(tmp, "%02X", b);
    Serial.print(tmp);
  }

  b = (uint8_t)(num & 0x00FF);
  sprintf(tmp, "%02X", b);
  Serial.print(tmp);
}

void p_(const char *a, const int b, const char *c = "") {
  Serial.print(a);
  Serial.print(" = [0x");
  phex(b);
  Serial.print("] <0b");
  for (int x = 7; x >= 0; x--) { Serial.print(bitRead(b, x)); }
  Serial.print("> ");
  Serial.print(b, DEC);
  Serial.print(" ");
  Serial.println(c);
}

void b_(const char *a, const bool b, const char *c = "") {
  Serial.print(a);
  Serial.print(" = ");
  Serial.print(b);
  Serial.print(" ");
  if (b) {
    Serial.print("TRUE");
  } else {
    Serial.print("false");
  }
  Serial.print(" ");
  Serial.println(c);
}


void q_(const char *a, const unsigned int d, const char *c = "") {
  Serial.print(a);
  Serial.print(" = [0x");
  phex(d, 4);
  Serial.print("] <0b");
  for (int x = 15; x >= 0; x--) { Serial.print(bitRead(d, x)); }
  Serial.print("> ");
  Serial.print(d, DEC);
  Serial.print(" ");
  Serial.println(c);
}

void n_(const char *a, const unsigned long d, const char *c = "") {
  Serial.print(a);
  Serial.print(" = ");
  Serial.print(d);
  Serial.print(" ");
  Serial.println(c);
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

  Serial.println("Tecsmith AMC6821 test!");

  // Try to initialize!
  if (!amc6821.begin()) {
    Serial.println("Failed to find AMC6821 chip");
    while (1) { delay(10); }
  }
  Serial.println("AMC6821 Found!");
  amc6821.start();

  looplimit = 2;
}

void loop() {
  // put your main code here, to run repeatedly:

  int32_t i;

  Serial.println("\n------------------------------------------------------------");

  p_("             Device ID", amc6821.getDeviceID());
  p_("            Company ID", amc6821.getCompanyID());
  p_("  Part Revision Number", amc6821.getPartRevision());

  Serial.println();

  p_("---- Config register 1", amc6821.getConfig(1));
  b_("         Start Monitor", amc6821.getStartMonitor());
  b_("     Global Int Enable", amc6821.getGlobalIntEnable());
  b_("        RPM Int Enable", amc6821.getRPMIntEnable());
  b_("            PWM Invert", amc6821.getPWMInvert());
  b_("  Fan Fault Pin Enable", amc6821.getFanFaultPinEnable());
  // ---
  Serial.print("      Fan Control Mode = ");
  amc6821_conf1_fdrc_t my_fdrc = amc6821.getFanControlMode();
  switch (my_fdrc) {
    case AMC6821_CONF1_FDRC_AUTO_REMOTE: Serial.println("AUTO_REMOTE"); break;
    case AMC6821_CONF1_FDRC_MAX_SPEED: Serial.println("MAX_SPEED"); break;
    case AMC6821_CONF1_FDRC_SOFTWARE_DCY: Serial.println("SOFTWARE_DCY"); break;
    case AMC6821_CONF1_FDRC_SOFTWARE_RPM: Serial.println("SOFTWARE_RPM"); break;
    default: Serial.println("Unknown!");
  }
  // ---
  b_("      Therm Int Enable", amc6821.getThermIntEnable());

  p_("---- Config register 2", amc6821.getConfig(2));
  b_("        PWM Out Enable", amc6821.getPWMOutEnable());
  b_("             Tach Mode", amc6821.getTachMode());
  b_("           Tach Enable", amc6821.getTachEnable());
  b_("Remote Fail Int Enable", amc6821.getRemoteFailureIntEnable());
  b_("         LT Int Enable", amc6821.getLTIntEnable());
  b_("         RT Int Enable", amc6821.getRTIntEnable());
  b_("       LPSV Int Enable", amc6821.getLPSVIntEnable());

  p_("---- Config register 3", amc6821.getConfig(3));
  b_("       Term Fan Enable", amc6821.getTermFanEnable());

  p_("---- Config register 4", amc6821.getConfig(4));
  b_("            OVR Enable", amc6821.getOVREnable());
  b_("     Tach Reading Fast", amc6821.getTachReadingFast());
  b_("          Pulse Number", amc6821.getPulseNumber());

  Serial.println();

  p_("---- Status register 1", amc6821.getStatus(1));
  b_("              Fan Fast", amc6821.getFanFast());
  b_("              Fan Slow", amc6821.getFanSlow());
  b_("      Remote Temp High", amc6821.getRTHigh());
  b_("       Remote Temp Low", amc6821.getRTLow());
  b_("Remote Temp Over Therm", amc6821.getRTOverTherm());
  b_("   Remote Temp Failure", amc6821.getRTFailure());
  b_("       Local Temp High", amc6821.getLTHigh());
  b_("        Local Temp Low", amc6821.getLTLow());

  p_("---- Status register 2", amc6821.getStatus(2));
  b_("Remote T Over Critical", amc6821.getRTOverCritical());
  b_(" Local T Over Critical", amc6821.getLTOverCritical());
  b_("Local Temp Below Therm", amc6821.getLTBelowTherm());
  b_(" Local Temp Over Therm", amc6821.getLTOverTherm());
  b_("            OVR Enable", amc6821.getThermInput());

  /* ---------------------------------------------------------------------- */

  Serial.println();

  p_("T Fractions 0bRRR__LLL", amc6821.read(AMC6821_REG_TEMP_LBYTE), "**");

  p_("     Local Temperature", amc6821.getLocalTemp(), "°C");
  i = amc6821.getLocalMilliTemp();
  Serial.print("                                             ");
  Serial.print((float)i/1000);
  Serial.println(" °C");

  p_("    Remote Temperature", amc6821.getRemoteTemp(), "°C");
  i = amc6821.getRemoteMilliTemp();
  Serial.print("                                             ");
  Serial.print((float)i/1000);
  Serial.println(" °C");

  p_(" Local High Temp Limit", amc6821.getLocalHighTempLimit(), "°C");
  p_("  Local Low Temp Limit", amc6821.getLocalLowTempLimit(), "°C");
  p_("     Local Therm Limit", amc6821.getLocalThermLimit(), "°C");
  p_("Remote High Temp Limit", amc6821.getRemoteHighTempLimit(), "°C");
  p_("  RemoteLow Temp Limit", amc6821.getRemoteLowTempLimit(), "°C");
  p_("    Remote Therm Limit", amc6821.getRemoteThermLimit(), "°C");
  p_("   Local Critical Temp", amc6821.getLocalCriticalTemp(), "°C");
  p_("  Passive Cooling Temp", amc6821.getPassiveCoolingTemp(), "°C");
  p_("  Remote Critical Temp", amc6821.getRemoteCriticalTemp(), "°C");

  Serial.println();

  p_("   Fan Characteristics", amc6821.getFanCharacteristics());
  p_("   Duty Cycle Low Temp", amc6821.getDutyCycleLowTemp());
  p_("            Duty Cycle", amc6821.getDutyCycle());
  p_("       Duty Cycle Ramp", amc6821.getDutyCycleRamp());
  p_("Local Temp Fan Control", amc6821.getLocalTempFanControl());
  p_("  Remote T Fan Control", amc6821.getRemoteTempFanControl());

  Serial.println();

  q_("             Tach Data", amc6821.getTachData());
  n_("             Tach Data", amc6821.getTachDataRPM(), "RPM");
  q_("        Tach Low Limit", amc6821.getTachLowLimit());
  n_("        Tach Low Limit", amc6821.getTachLowLimitRPM(), "RPM");
  q_("       Tach High Limit", amc6821.getTachHighLimit());
  n_("       Tach High Limit", amc6821.getTachHighLimitRPM(), "RPM");
  q_("          Tach Setting", amc6821.getTachSetting());
  n_("          Tach Setting", amc6821.getTachSettingRPM(), "RPM");

  Serial.println("------------------------------------------------------------\n");
  delay(1000);
  if (looplimit <= 0) { while (1) delay(19000); } else { looplimit--; }
}
