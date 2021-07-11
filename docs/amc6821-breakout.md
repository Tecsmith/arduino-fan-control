AMC6821 Breakout Board
======================

- GitHub repository here: [github.com/Tecsmith/arduino-fan-control-v2](https://github.com/Tecsmith/arduino-fan-control-v2)

Specifications
--------------

- Host for [Texas Instruments AMC6821](https://www.ti.com/lit/gpn/amc6821) Intelligent Temperature Monitor and PWM Fan Controller
- Powered from 12V + 5V power supply
  * or just 12V with optional 12V-to-5V ("7805" IC or Pololu 5V Step-Down) regulator
  * or just 5V for 5V fans
- I<sup>2</sup>C breakout pins (SCL, SDA, 3V3, GND)
  * on board 3.3KΩ pullups, disable by severing JP1
- AMC6821 breakout pins (PWM, TACH, <u>OVR</u>, <u>THERM</u>, <u>FAN-FAULT</u>, <u>SMBALERT</u>)
- Power LED (green)
- Error LEDs (red) (OVR, THERM, FAN-FAULT)
- 2x Qwiic connector (works with SparkFun's [Qwiic Connect System](https://www.sparkfun.com/qwiic))
- Supports 2x PWM Modes
- Supports 9x I<sup>2</sup>C Addresses
- Supports most industry FAN types
  - JST 2-wire connector
    * 5V, 2-wire
  - Molex 4-wire KK-254-47053-1000 connector
    * 12V, 2-wire
    * 12V, 3-wire, with Tachometer
    * 12V, 3-wire, with Rotor-Lock
    * 12V PWM, 4-wire, with Tachometer & PWM control
- Includes on board Temperature sensor
  * can be isolated (sever JP5 and JP6) for BYO sensor
  * can be cut out for remote installation

On Board Jumpers
----------------

### JP1 - I<sup>2</sup>C Pullups
- Connected _(default)_: 3.3KΩ pullups
- Cut both sides: No pullups

### JP2 & JP3 (A0 & A1) - I<sup>2</sup>C Address Selector

A0 / JP2 | A1 / JP3 | 7-bit | Address
---|---|---|---
GND | GND | 0011000 | 24 _(Default)_
N/C | GND | 0011010 | 26
3V3 | GND | 0011001 | 25
GND | N/C | 0101100 | 44
N/C | N/C | 0101110 | 46
3V3 | N/C | 0101001 | 45
GND | 3V3 | 1001100 | 76
N/C | 3V3 | 1001110 | 78
3V3 | 3V3 | 1001101 | 77

### JP4 - <u>PWM-MODE</u> / PWM Frequency

- Tied to GND: High Frequency range, 1kHz to 40kHz _(Default 25kHz)_
- Tied to 3V3: Low Frequency range, 10Hz to 94Hz
- Actual PWM Frequency depends on Fan Characteristics Register, bits 3-5

### JP5 & JP6 - Optional Temperature Sensor

- Both tied: Sensor enabled _(Default)_
- Both cut: Sensor disabled, use J7 to connect external sensor

### JP7 - PWM Inverter

- Tied to PWM-OUT: PWM from AMC6821 _(Default)_
- Tied to <u>PWM-OUT</u>: PWM inverted from Schmitt-trigger
- Both cut: PWM disabled
- Both tied: PWM shorted, no PWM control

### FAN Wire Header _(J12)_

As view from top

#### 12V PWM FAN _(4-wire)_

GND | &middot; | &middot; | **[&middot;** | **&middot;]** | FAN GND direct to GND
PWM | | &middot; | **[&middot;** | **&middot;]** | PWM sent to pin 4

#### 12V FAN _(3-wire & 2-wire variant)_

GND | &middot; | **[&middot;** | **&middot;]** | &middot; | FAN GND to MOSFET Drain
PWM | | **[&middot;** | **&middot;]** | &middot; | PWM sent to MOSFET

#### 5V FAN _(2-wire)_

GND | **[&middot;** | **&middot;]** | &middot; | &middot; | 5V FAN GND to MOSFET Drain _(12V FAN GND disabled)_
PWM | | **[&middot;** | **&middot;]** | &middot; | PWM sent to MOSFET



Manufacturing
-------------

![](img/amc6-top.png) ![](img/amc6-btm.png)

Initial prototype built by JCLPCB.com



<p align="center">★</p>
