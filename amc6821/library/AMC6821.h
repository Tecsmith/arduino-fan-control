/**
 *  Copyright (c) Vino Rodrigues
 */

#ifndef AMC6821_H
#define AMC6821_H

#include <Stdint.h>
#include <Wire.h>    // http://arduino.cc/en/Reference/Wire

#define AMC6821_I2C_ADDR_GG 0x18
#define AMC6821_I2C_ADDR_NG 0x1A
#define AMC6821_I2C_ADDR_VG 0x19
#define AMC6821_I2C_ADDR_GN 0x2C
#define AMC6821_I2C_ADDR_NN 0x2E
#define AMC6821_I2C_ADDR_VN 0x2D
#define AMC6821_I2C_ADDR_GV 0x4C
#define AMC6821_I2C_ADDR_NV 0x4E
#define AMC6821_I2C_ADDR_VV 0x4D
#define AMC6821_I2C_ADDRESS AMC6821_I2C_ADDR_VV

// Helpers
#define temperatureCToF(C) (C * 9 / 5 + 32)
#define temperatureFToC(F) ((F - 32) * 5 / 9)

enum amc6821_fan_control_mode_t { 
  amc6821_fdrc_software_dcy, 
  amc6821_fdrc_software_rpm,
  amc6821_fdrc_auto_remote, 
  amc6821_fdrc_auto_fastest };

enum amc6821_pwm_frequency {
  amc6821_pwmf_10hz = 0,
  amc6821_pwmf_15hz,
  amc6821_pwmf_23hz,
  amc6821_pwmf_30hz,
  amc6821_pwmf_38hz,
  amc6821_pwmf_47hz,
  amc6821_pwmf_62hz,
  amc6821_pwmf_94hz };

enum amc6821_spin_up_time {
  amc6821_sut_02s = 0,
  amc6821_sut_04s,
  amc6821_sut_06s,
  amc6821_sut_08s,
  amc6821_sut_1s,
  amc6821_sut_2s,
  amc6821_sut_4s,
  amc6821_sut_8s };

enum amc6821_slope_auto_temp_fan_control {
  amc6821_satfc_32 = 0,
  amc6821_satfc_16,
  amc6821_satfc_8,
  amc6821_satfc_4,
  amc6821_satfc_2 };

// enum fan_control_tach_t { tach_data, tach_low_limit, tach_high_limit, tach_setting };

class AMC6821
{
  public:
    AMC6821(uint8_t addr = 0);
    
    // Configuration Registers
    void setTHERMOVIE( bool enable = true );
    void setFDRC( amc6821_fan_control_mode_t fcm );
    void setFANFaultEN( bool enable = true );
    void setPWMINV( bool enable = true );
    void setFANIE( bool enable = true );
    void setINTEN( bool enable = true );
    void setSTART( bool enable = true );
    void setRST( bool enable = true );
    void setPSVIE( bool enable = true );
    void setRTOIE( bool enable = true );
    void setLTOIE( bool enable = true );
    void setRTFIE( bool enable = true );
    void setTACHEN( bool enable = true );
    void setTACHMODE( bool enable = true );
    void setPWMEN( bool enable = true );
    void setTHERMFANEN( bool enable = true );
    void setTachFast( bool enable = true );
    void setOvrInt( bool enable = true );
    
    void start();
    void reset();

    // Thermal Monitoring
    int8_t getLT8ths();
    int8_t getHT8ths();
    int8_t getLT();
    int8_t getRT();
    int8_t getLTH();
    int8_t getLTL();
    int8_t getLTT();
    int8_t getRTH();
    int8_t getRTL();
    int8_t getRTT();
    int8_t getLTC();
    int8_t getPSV();
    int8_t getRTC();

    void setLTH( int8_t value );
    void setLTL( int8_t value );
    void setLTT( int8_t value );
    void setRTH( int8_t value );
    void setRTL( int8_t value );
    void setRTT( int8_t value );
    void setLTC( int8_t value );
    void setPSV( int8_t value );
    void setRTC( int8_t value );

    // PWM Control
    bool getFSPD();
    amc6821_pwm_frequency getPWM();
    amc6821_spin_up_time getSTIME();
    uint8_t getDCYLT();
    uint8_t getDCY();
    int8_t getLLTC();
    amc6821_slope_auto_temp_fan_control getLSLP();
    int8_t getRLTC();
    amc6821_slope_auto_temp_fan_control getRSLP();

    void setFSPD( bool enable = true );
    void setPWM( amc6821_pwm_frequency value );
    void setSTIME( amc6821_spin_up_time value );
    void setDCYLT( uint8_t value );
    void setDCY( uint8_t value );
    void setLLTC( int8_t value );
    void setLSLP( amc6821_slope_auto_temp_fan_control value );
    void setRLTC( int8_t value );
    void setRSLP( amc6821_slope_auto_temp_fan_control value );

    //
    
    // int16_t readSpeed( fan_control_tach_t fct );
    // int16_t readRPM( fan_control_tach_t fct );
    // void setSpeed( fan_control_tach_t fct, int16_t value );
    // void setRPM( fan_control_tach_t fct, int16_t value );

  private:
    uint8_t _addr;
  protected:
    static void setFlag(uint8_t addr, uint8_t reg, uint8_t flag, bool en);
    static void setFlags(uint8_t addr, uint8_t reg, uint8_t mask, uint8_t value);
    static uint8_t read1(uint8_t addr, uint8_t reg);
    static void write1(uint8_t addr, uint8_t reg, uint8_t data); 
};

extern AMC6821 amc6821;

#endif
