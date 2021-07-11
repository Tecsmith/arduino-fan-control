# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

[[[[[ **This project is in WIP state.** ]]]]]

## [Unreleased]

### Added

- Rebuild of PlatformIO examples

### Removed

- Sub projects removed (and added to their own GitHub projects)
  * [arduino-esp-01-dev-board](https://github.com/Tecsmith/arduino-esp-01-dev-board)
  * [arduino-pro-micro-screw-terminal](https://github.com/Tecsmith/arduino-pro-micro-screw-terminal)
  * [arduino-wemos-d1-screw-terminal](https://github.com/Tecsmith/arduino-wemos-d1-screw-terminal)
  * arduino-emc2101 *(deleted)*

### Changed

- Arduino examples renamed.  These will stay, but not be maintained or added on as PlatformIO is the preferred environment.

## [2.3.0] - 2020-12-17

### Added

- Initial AMC6820 and SMBus libraries
- WIP PlatformIO code to test IC integration

### Changed

- Realized that JP2 = A0 and JP3 = A1 could lead to confusion, renamed all JP's (with J0 = A0 & J1 = A1)
- Created expanded solder pads on Optional Temp. Sensor to allow for horizontal cable soldering.
- Moved Qwiic connectors up by 25mil to allow better clearance of mounting screws.
- Issue identified with JLCPCB validation
    + C7 (Optional Temp. Sensor capacitor) was the incorrect footprint, changed from 0402 to 0805.  This is a breaking error, however, since sensor is optional will not impact development of firmware.
    + Q2, Q3, Q4 (Red LED inversion transistors) were the incorrect footprint.  Non-breaking.  Changed to SOT23-3. Moved the route airwires to accommodate.

## [2.2.0] - 2020-12-05

### Changed

- Fix for the Qwiic connector being oriented the wrong way

## [2.1.0] - ?

- Unreleased

## [2.0.0] - 2020-11-02

### Added
- Initial release (and first production run with [JLCPCB](https://jlcpcb.com/))
