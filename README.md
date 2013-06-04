Arduino Fan Control Module
==========================

About
-----

All electronics projects have the potential to generate excessive heat.
Fans are one of the most common methods for thermal management, but can also add significant power consumption and noise.
Having a fan state/speed controlled by temperature levels can reduce these, but having the Arduino control these independantly adds complexity to the project.

This project is a colection of modules that allow you to add fans to your Arduino project, and automate the fan speed/state by removing the requirement for the Arduino project to manage them in real-time, yet give you the ability to do so.

Features
--------

* Managed by I2C communication, so can be used in other mini-boards like the Raspberry Pi
* Controls 1 to 4 5V or 12V fans, either 3-wire or 4-wire (support for both) using PWM
	* Default to 4-wire, but add through-hole or jumpers for MOSFET to control 3-wire
* Works on both 3.3V and 5V variants of Arduino (Due or Leonardo)
* 1x remote Temperature measure headers per fan (thermal diodes not included)

**(V)(;,,;)(V)**
