# MrAqua Aquarium Controller

This project was based off the iAqua controller written by Dan Cunningham with new features and updates here.

![Controller home screen](https://i.imgur.com/75ALPY3.jpg)

## Features

- Water temperature monitoring
  - Allows calibration
  - Automatic shutoff of heater if water exceeds setpoint
- Automatic water top-off 
  - Float switch inputs for tank and reservoir
  - Set maximum run-time with alarm flagged if exceeded
- Feeding mode
  - Monitor time since last fed
  - Control outlets during feeding (ie turn off pumps)
- Light control 
  - 6-channel PWM or IR control of e-series LED
  - 4 lighting levels (moonlight, sunrise, mid-morning and full daylight)
- Dosing
  - 3 channels
  - Individual settings for each channel
- 8 power outlet control
  - Manual control or set on/off times
  - Aux outlets can be set to cycle times (ie on 10 minutes every 2 hours)


## Hardware

- Arduino Mega
- 320 x 240 LCD
- Arduino Mega TFT Shield (or custom shield below)
- 12V power supply
- 8 channel relay board
- DS18B20 temperature sensor
- Peristaltic pumps
- Float switch
- Submersible 12V pump
- (Optional)PCA9685 breakout board


## Libraries

- [Adafruit PWM Servo Driver](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library)
- [Dallas Temperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)
- [Time Library](https://github.com/PaulStoffregen/Time)
- [Arduino IR Remote](https://github.com/z3t0/Arduino-IRremote)
- [DS1307RTC](https://github.com/PaulStoffregen/DS1307RTC)
- [SdFat](https://github.com/greiman/SdFat)
- [TimeAlarms](https://github.com/PaulStoffregen/TimeAlarms)
- [UTFT](http://www.rinkydinkelectronics.com/library.php?id=51)
- [UTFT_SdRaw](https://platformio.org/lib/show/565/UTFT_SdRaw)
- [URTouch](http://www.rinkydinkelectronics.com/library.php?id=92)


## Setup

If you are using an ecoxotic e-series LED set "lightCSP" to true, otherwise set it to false.  If you are using a PCA9685 chip for PWM set boolean "PCA9685Installed" to true.
