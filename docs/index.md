# Qwiic Fan Control Module


AMC6821 based Fan Control Module with Qwiic connectors for integration into 3.3V MCU projects.

GitHub repository at [Tecsmith/arduino-fan-control](https://github.com/Tecsmith/arduino-fan-control)

## Features / Specifications

> This project contains 2 PCB boards:
> * AMC6821 Breakout Board
> * Fan Host Board
>   * *(supports both the above board and the [Adafruit EMC2101 Breakout Board](https://www.adafruit.com/product/4808))*


### AMC6821 Breakout Board

- Host for [Texas Instruments AMC6821](https://www.ti.com/lit/gpn/amc6821) Intelligent Temperature Monitor and PWM Fan Controller
- Integrats into other 3.3V based MCU's (via Qwiic / STEMMA QT connectors) 
- I<sup>2</sup>C breakout pins (SCL, SDA, 3V3, GND)
  * on board 3.3KΩ pullups, disable by cutting jumpers
- AMC6821 breakout pins (PWM, TACH, <u>FAN-FAULT</u> and <u>SMBALERT</u>. <u>OVR</u> and <u>THERM</u> are also available.)
- Power LED (green)
- 2x Qwiic connector (works with SparkFun's [Qwiic Connect System](https://www.sparkfun.com/qwiic), or Adafruit's [STEMMA QT](https://www.adafruit.com/?q=stemma+qt))
- Supports 2x PWM Modes (via Jumper)
- Supports 9x I<sup>2</sup>C Addresses (via Jumper)
- Includes an on board Temperature sensor
  * <s>can be cut out for remote installation (use rotary cutter along breakm line)</s>

### Fan Host Board

- Powered from 12V + 5V power supply
  * or just 12V with optional 12V-to-5V ("7805" IC or Pololu 5V Step-Down) regulator
  * or just 5V for 5V fans
- Supports most industry FAN types
  - Molex 4-wire `KK-254-47053-1000` connector
    * 12V PWM, 4-wire, with Tachometer & PWM control
    * 12V, 3-wire, with Tachometer
    * 12V, 3-wire, with Rotor-Lock
    * 12V, 2-wire
  - JST 2-wire connector
    * 5V, 2-wire

### <s>Not is scope</s>

- <s>Stand alone operation. Best use of this controller requires interaction with an underlying system.</s>
- <s>Error LEDs (red) (OVR, THERM, FAN-FAULT) - requires schmitt trigger inverters</s>


----------

## AMC6821 Breakout Board


| Top | Bottom |
|:---:|:------:|
| <img src="img/amc6-bo-t.png" height="300" width="405"> | <img src="img/amc6-bo-b.png" height="300" width="405"> |

Files:
* Schematic: [`amc6821-breakout-v3.0`](amc6821-breakout-v3.0.pdf)


----------

## Fan Host Board

| Top / Bottom |
|:---:|
| <img src="img/fanctrl-t.png" height="300" width="540"> |
| <img src="img/fanctrl-b.png" height="300" width="540"> |

Files:
* Schematic: [`fan-host-board-v1.0`](fan-host-board-v1.0.pdf)


----------

## Source Code

Currently under development ... refer to:

* PlatfromIO examples: [Tecsmith/arduino-fan-control/PlatformIO](https://github.com/Tecsmith/arduino-fan-control/tree/master/PlatformIO)
* AMC6821 Library: [Tecsmith/Tecsmith_AMC6821](https://github.com/Tecsmith/Tecsmith_AMC6821)


----------
<p align="center" style="color:#069">★</p>
