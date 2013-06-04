/**
 *  Copyright (c) Vino Rodrigues
 */

#include "AMC6821.h"

#define AMC6821_REG_DEV_ID 0x3D
#define AMC6821_REG_COMP_ID 0x3E
#define AMC6821_REG_CONF1 0x00
#define AMC6821_REG_CONF2 0x01
#define AMC6821_REG_CONF3 0x3F
#define AMC6821_REG_CONF4 0x04
#define AMC6821_REG_STAT1 0x02
#define AMC6821_REG_STAT2 0x03
#define AMC6821_REG_TEMP_8THS 0x06
#define AMC6821_REG_TDATA_LOW 0x08
#define AMC6821_REG_TDATA_HI 0x09
#define AMC6821_REG_LTEMP_HI 0x0A
#define AMC6821_REG_RTEMP_HI 0x0B
#define AMC6821_REG_LTEMP_LIMIT_MIN 0x15
#define AMC6821_REG_LTEMP_LIMIT_MAX 0x14
#define AMC6821_REG_RTEMP_LIMIT_MIN 0x19
#define AMC6821_REG_RTEMP_LIMIT_MAX 0x18
#define AMC6821_REG_LTEMP_CRIT 0x1B
#define AMC6821_REG_RTEMP_CRIT 0x1D
#define AMC6821_REG_LTEMP_THERM 0x16
#define AMC6821_REG_RTEMP_THERM 0x1A
#define AMC6821_REG_PSV_TEMP 0x1C
#define AMC6821_REG_FAN_CHAR 0x20
#define AMC6821_REG_DCY_LOW_TEMP 0x21
#define AMC6821_REG_DCY 0x22
#define AMC6821_REG_LTEMP_FAN_CTRL 0x24
#define AMC6821_REG_RTEMP_FAN_CTRL 0x25

#define AMC6821_REG_TACH_LLIMITL 0x10
#define AMC6821_REG_TACH_LLIMITH 0x11
#define AMC6821_REG_TACH_HLIMITL 0x12
#define AMC6821_REG_TACH_HLIMITH 0x13
#define AMC6821_REG_TACH_SETTINGL 0x1E
#define AMC6821_REG_TACH_SETTINGH 0x1F

#define AMC6821_CONF1_START 0x01
#define AMC6821_CONF1_FAN_INT_EN 0x02
#define AMC6821_CONF1_FANIE 0x04
#define AMC6821_CONF1_PWMINV 0x08
#define AMC6821_CONF1_FAN_FAULT_EN 0x10
#define AMC6821_CONF1_FDRC0 0x20
#define AMC6821_CONF1_FDRC1 0x40
#define AMC6821_CONF1_THERMOVIE 0x80

#define AMC6821_CONF2_PWM_EN 0x01
#define AMC6821_CONF2_TACH_MODE 0x02
#define AMC6821_CONF2_TACH_EN 0x04
#define AMC6821_CONF2_RTFIE 0x08
#define AMC6821_CONF2_LTOIE 0x10
#define AMC6821_CONF2_RTOIE 0x20
#define AMC6821_CONF2_PSVIE 0x40
#define AMC6821_CONF2_RST 0x80

#define AMC6821_CONF3_THERM_FAN_EN 0x80
#define AMC6821_CONF3_REV_MASK 0x0F

#define AMC6821_CONF4_OVREN 0x10
#define AMC6821_CONF4_TACH_FAST 0x20
#define AMC6821_CONF4_PSPR 0x40
#define AMC6821_CONF4_MODE 0x80

#define AMC6821_STAT1_RPM_ALARM 0x01
#define AMC6821_STAT1_FANS 0x02
#define AMC6821_STAT1_RTH 0x04
#define AMC6821_STAT1_RTL 0x08
#define AMC6821_STAT1_R_THERM 0x10
#define AMC6821_STAT1_RTF 0x20
#define AMC6821_STAT1_LTH 0x40
#define AMC6821_STAT1_LTL 0x80

#define AMC6821_STAT2_RTC 0x08
#define AMC6821_STAT2_LTC 0x10
#define AMC6821_STAT2_LPSV 0x20
#define AMC6821_STAT2_L_THERM 0x40
#define AMC6821_STAT2_THERM_IN 0x80

/* ===== Public ===== */

AMC6821::AMC6821(uint8_t addr) {
  if (addr == 0) _addr = AMC6821_I2C_ADDR_VV;
  else _addr = addr;
}

/* ----- Configuration Registers ----- */

void AMC6821::setTHERMOVIE(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF1, AMC6821_CONF1_THERMOVIE, enable);
}

void AMC6821::setFDRC( amc6821_fan_control_mode_t fcm ) {
  switch (fcm) {
    case amc6821_fdrc_software_dcy : 
      setFlags(_addr, AMC6821_REG_CONF1, AMC6821_CONF1_FDRC0 + AMC6821_CONF1_FDRC1,
        0);
      break;
    case amc6821_fdrc_software_rpm : 
      setFlags(_addr, AMC6821_REG_CONF1, AMC6821_CONF1_FDRC0 + AMC6821_CONF1_FDRC1,
        AMC6821_CONF1_FDRC0);
      break;
    case amc6821_fdrc_auto_remote : 
      setFlags(_addr, AMC6821_REG_CONF1, AMC6821_CONF1_FDRC0 + AMC6821_CONF1_FDRC1,
        AMC6821_CONF1_FDRC1);
      break;
    case amc6821_fdrc_auto_fastest : 
      setFlags(_addr, AMC6821_REG_CONF1, AMC6821_CONF1_FDRC0 + AMC6821_CONF1_FDRC1,
        AMC6821_CONF1_FDRC0 + AMC6821_CONF1_FDRC1);
      break;
  }
}

void AMC6821::setFANFaultEN(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF1, AMC6821_CONF1_FAN_FAULT_EN, enable);
}

void AMC6821::setPWMINV(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF1, AMC6821_CONF1_PWMINV, enable);
}

void AMC6821::setFANIE(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF1, AMC6821_CONF1_FAN_INT_EN, enable);
}

void AMC6821::setINTEN(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF1, AMC6821_CONF1_FAN_INT_EN, enable);
}

void AMC6821::setSTART(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF1, AMC6821_CONF1_START, enable);
}

void AMC6821::start() { setSTART(true); }

void AMC6821::setRST( bool enable ) {
  write1(_addr, AMC6821_REG_CONF2, AMC6821_CONF2_RST);
}

void AMC6821::reset() { setRST(true); }

void AMC6821::setPSVIE(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF2, AMC6821_CONF2_PSVIE, enable);
}

void AMC6821::setRTOIE(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF2, AMC6821_CONF2_RTOIE, enable);
}

void AMC6821::setLTOIE(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF2, AMC6821_CONF2_LTOIE, enable);
}

void AMC6821::setRTFIE(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF2, AMC6821_CONF2_RTFIE, enable);
}

void AMC6821::setTACHEN(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF2, AMC6821_CONF2_TACH_EN, enable);
}

void AMC6821::setTACHMODE(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF2, AMC6821_CONF2_TACH_MODE, enable);
}

void AMC6821::setPWMEN(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF2, AMC6821_CONF2_PWM_EN, enable);
}

void AMC6821::setTHERMFANEN(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF3, AMC6821_CONF3_THERM_FAN_EN, enable);
}

void AMC6821::setTachFast(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF4, AMC6821_CONF4_TACH_FAST, enable);
}

void AMC6821::setOvrInt(bool enable) {
  setFlag(_addr, AMC6821_REG_CONF4, AMC6821_CONF4_OVREN, enable);
}

/* ----- Thermal Monitoring ----- */

int8_t AMC6821::getLT8ths() {
  return (read1(_addr, AMC6821_REG_TEMP_8THS) >> 5) & 0x07;
}

int8_t AMC6821::getHT8ths() {
  return read1(_addr, AMC6821_REG_TEMP_8THS) & 0x07;
}

int8_t AMC6821::getLT() {
  return (int8_t)read1(_addr, AMC6821_REG_LTEMP_HI);
}

int8_t AMC6821::getRT() {
  return (int8_t)read1(_addr, AMC6821_REG_RTEMP_HI);
}

int8_t AMC6821::getLTH() {
  return (int8_t)read1(_addr, AMC6821_REG_LTEMP_LIMIT_MAX);
}

int8_t AMC6821::getLTL() {
  return (int8_t)read1(_addr, AMC6821_REG_LTEMP_LIMIT_MIN);
}

int8_t AMC6821::getLTT() {
  return (int8_t)read1(_addr, AMC6821_REG_LTEMP_THERM);
}

int8_t AMC6821::getRTH() {
  return (int8_t)read1(_addr, AMC6821_REG_RTEMP_LIMIT_MAX);
}

int8_t AMC6821::getRTL() {
  return (int8_t)read1(_addr, AMC6821_REG_RTEMP_LIMIT_MIN);
}

int8_t AMC6821::getRTT() {
  return (int8_t)read1(_addr, AMC6821_REG_RTEMP_THERM);
}

int8_t AMC6821::getLTC() {
  return (int8_t)read1(_addr, AMC6821_REG_LTEMP_CRIT);
}

int8_t AMC6821::getPSV() {
  return (int8_t)read1(_addr, AMC6821_REG_PSV_TEMP);
}

int8_t AMC6821::getRTC() {
  return (int8_t)read1(_addr, AMC6821_REG_RTEMP_CRIT);
}

void AMC6821::setLTH( int8_t value ) {
  write1( _addr, AMC6821_REG_LTEMP_LIMIT_MAX, (uint8_t)value );
}

void AMC6821::setLTL( int8_t value ) {
  write1( _addr, AMC6821_REG_LTEMP_LIMIT_MIN, (uint8_t)value );
}

void AMC6821::setLTT( int8_t value ) {
  write1( _addr, AMC6821_REG_LTEMP_THERM, (uint8_t)value );
}

void AMC6821::setRTH( int8_t value ) {
  write1( _addr, AMC6821_REG_RTEMP_LIMIT_MAX, (uint8_t)value );
}

void AMC6821::setRTL( int8_t value ) {
  write1( _addr, AMC6821_REG_RTEMP_LIMIT_MIN, (uint8_t)value );
}

void AMC6821::setRTT( int8_t value ) {
  write1( _addr, AMC6821_REG_RTEMP_THERM, (uint8_t)value );
}

void AMC6821::setLTC( int8_t value ) {
  write1( _addr, AMC6821_REG_LTEMP_CRIT, (uint8_t)value );
}

void AMC6821::setPSV( int8_t value ) {
  write1( _addr, AMC6821_REG_PSV_TEMP, ((uint8_t)value & 0x3F) );
}

void AMC6821::setRTC( int8_t value ) {
  write1( _addr, AMC6821_REG_RTEMP_CRIT, (uint8_t)value );
}

/* ----- PWM Control ----- */

bool AMC6821::getFSPD() {
  return (read1(_addr, AMC6821_REG_FAN_CHAR) & 0x80) != 0;
}

amc6821_pwm_frequency AMC6821::getPWM() {
  return (amc6821_pwm_frequency)((read1(_addr, AMC6821_REG_FAN_CHAR) & 0x38) >> 3);
}

amc6821_spin_up_time AMC6821::getSTIME() {
  return (amc6821_spin_up_time)(read1(_addr, AMC6821_REG_FAN_CHAR) & 0x07);
}

uint8_t AMC6821::getDCYLT() {
  return read1(_addr, AMC6821_REG_DCY_LOW_TEMP);
}

uint8_t AMC6821::getDCY() {
  return read1(_addr, AMC6821_REG_DCY);
}

int8_t AMC6821::getLLTC() {}
amc6821_slope_auto_temp_fan_control AMC6821::getLSLP() {}
int8_t AMC6821::getRLTC() {}
amc6821_slope_auto_temp_fan_control AMC6821::getRSLP() {}



void AMC6821::setFSPD( bool enable ) {
  setFlag(_addr, AMC6821_REG_FAN_CHAR, 0x80, enable);
}

void AMC6821::setPWM( amc6821_pwm_frequency value ) {
  setFlags(_addr, AMC6821_REG_FAN_CHAR, 0x38, ( (uint8_t)value << 3 ));
}

void AMC6821::setSTIME( amc6821_spin_up_time value ) {
  setFlags(_addr, AMC6821_REG_FAN_CHAR, 0x07, ( (uint8_t)value ));
}

void AMC6821::setDCYLT( uint8_t value ) {
  write1(_addr, AMC6821_REG_DCY_LOW_TEMP, value);
}

void AMC6821::setDCY( uint8_t value ) {
  write1(_addr, AMC6821_REG_DCY, value);
}

void AMC6821::setLLTC( int8_t value ) {}
void AMC6821::setLSLP( amc6821_slope_auto_temp_fan_control value ) {}
void AMC6821::setRLTC( int8_t value ) {}
void AMC6821::setRSLP( amc6821_slope_auto_temp_fan_control value ) {}


/* int8_t AMC6821::readTemp( fan_control_temp_t fct ) {
  int8_t t;
  switch (fct) {
    case local_fan_ctrl: 
      t = ((int8_t)read1(_addr, AMC6821_REG_LTEMP_FAN_CTRL) & 0xF8) >> 2;
      break;
    case remote_fan_ctrl: 
      t = ((int8_t)read1(_addr, AMC6821_REG_RTEMP_FAN_CTRL) & 0xF8) >> 2;
      break;
    case high_temp: 
      t := readTemp( remote_low_limit );
      break;
  }
  return t;
} */


/*
int16_t AMC6821::readSpeed( fan_control_tach_t fct ) {
  uint8_t lo, hi;
  uint16_t tach;
  switch (fct) {
    case tach_data: lo = AMC6821_REG_TDATA_LOW; hi = AMC6821_REG_TDATA_HI; break;
    case tach_low_limit: lo = AMC6821_REG_TACH_HLIMITL; hi = AMC6821_REG_TACH_HLIMITH; break;
    case tach_high_limit: lo = AMC6821_REG_TACH_LLIMITL; hi = AMC6821_REG_TACH_LLIMITH; break;
    case tach_setting: lo = AMC6821_REG_TACH_SETTINGL; hi = AMC6821_REG_TACH_SETTINGH; break;
  }
  tach = read1(_addr, lo);
  tach += (read1(_addr, hi) << 8);
  return tach;
}

int16_t AMC6821::readRPM( fan_control_tach_t fct ) {
  int16_t tach = readSpeed( fct );
  if (tach > 0) return (6000000 / tach);
  else return -1;
}

void AMC6821::setSpeed( fan_control_tach_t fct, int16_t value ) {
  uint8_t lo, hi, val;
  switch (fct) {
    case tach_low_limit: lo = AMC6821_REG_TACH_HLIMITL; hi = AMC6821_REG_TACH_HLIMITH; break;
    case tach_high_limit: lo = AMC6821_REG_TACH_LLIMITL; hi = AMC6821_REG_TACH_LLIMITH; break;
    case tach_setting: lo = AMC6821_REG_TACH_SETTINGL; hi = AMC6821_REG_TACH_SETTINGH; break;
    default: return; break;
  }
  val = value & 0x00FF;
  write1(_addr, lo, val);
  val = value >> 8;
  write1(_addr, hi, val);
}

void AMC6821::setRPM( fan_control_tach_t fct, int16_t value ) {
  setSpeed( fct, (6000000 / value) );
}
*/

/* ===== Protected ===== */

void AMC6821::setFlag(uint8_t addr, uint8_t reg, uint8_t flag, bool enable) {
  uint8_t cnf = read1(addr, reg);
  if (enable) cnf |= flag;
  else cnf &= ~flag;
  write1(addr, reg, cnf);
}

void AMC6821::setFlags(uint8_t addr, uint8_t reg, uint8_t mask, uint8_t value) {
  uint8_t cnf = read1(addr, reg);
  cnf &= ~mask;
  cnf |= value;
  write1(addr, reg, cnf);
}

uint8_t AMC6821::read1(uint8_t addr, uint8_t reg) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(addr, (uint8_t)1);
  if (Wire.available()) {
    return Wire.read();
  } else {
    return 0xFF;
  }
}

void AMC6821::write1(uint8_t addr, uint8_t reg, uint8_t data) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

AMC6821 amc6821 = AMC6821();