# Qwiic Fan Control Module

-----

| **&#9888; WARNING &#9888;** |
|:---------------------------:|
| The v2.3 design does not work.  There is a flaw in the PWM design that I cannot resolve yet. |

-----


AMC6821 based Fan Control Module with Qwiic connectors for integration into 3.3V MCU projects.

GitHub repository at [Tecsmith/arduino-fan-control](https://github.com/Tecsmith/arduino-fan-control)

## Features / Specifications

- Host for [Texas Instruments AMC6821](https://www.ti.com/lit/gpn/amc6821) Intelligent Temperature Monitor and PWM Fan Controller
- Can operate in two modes:
  - Standalone
  - Integrated (via Qwiic/STEMMA connectors) with 3.3V based MCU's
- <s>Powered from 12V + 5V power supply</s>
  * <s>or just 12V with optional 12V-to-5V ("7805" IC or Pololu 5V Step-Down) regulator</s>
  * <s>or just 5V for 5V fans</s>
- I<sup>2</sup>C breakout pins (SCL, SDA, 3V3, GND)
  * on board 3.3KΩ pullups, disable by cutting JP1
- AMC6821 breakout pins (PWM, TACH, <u>OVR</u>, <u>THERM</u>, <u>FAN-FAULT</u>, <u>SMBALERT</u>)
- Power LED (green)
- <s>Error LEDs (red) (OVR, THERM, FAN-FAULT)</s>
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
- <s>Includes on board Temperature sensor</s>
  * <s>can be isolated (cut JP5 and JP6) for BYO sensor</s>
  * <s>can be cut out for remote installation (use rotary cutter along drill holes)</s>

----------


## Source Code

Currently under development ... refer to:

* PlatfromIO examples: [Tecsmith/arduino-fan-control/PlatformIO](https://github.com/Tecsmith/arduino-fan-control/tree/master/PlatformIO)
* AMC6821 Library: [Tecsmith/Tecsmith_AMC6821](https://github.com/Tecsmith/Tecsmith_AMC6821)

----------
<p align="center" style="color:#069">★</p>
