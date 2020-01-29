# NOI Techpark - E-Paper Displays

A project to create an E-Paper Display in front of each office, which can be
updated and controlled remotely.

Currently, we are testing several methods with Arduino UNO and Waveshare e-Paper
Shields. See our [playground](/playground/) for some ideas.

The final implementation can then be found under the following repositories:
- [BACKEND](https://github.com/noi-techpark/e-ink-displays-backend) for Arduino low-level code
- [WEB APP](https://github.com/noi-techpark/e-ink-displays-webapp) to manage locations, displays and image uploads
- [JAVA API](https://github.com/noi-techpark/e-ink-displays-api) as a backbone for the web app

**Example**
![First Prototype](/first-prototype.jpg)

## Getting started

Install the [Arduino IDE](https://www.arduino.cc/en/Main/Software) or use the
online version of it. If you want to use Visual Studio Code as editor, install
the corresponding
[extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)
and configure it.

Example configuration inside a `.vscode` folder.

File: `c_cpp_properties.json` (substitute paths accordingly)
```json
{
    "env": {
        "arduino.path": "${HOME}/.arduino15/packages/arduino",
        "arduino.avr.include.path": "${env:arduino.path}/hardware/avr/1.8.1",
        "arduino.avr.compiler.path": "${env:arduino.path}/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin/avr-g++",
        "arduino.libraries.path": "${HOME}/Arduino/libraries"
    },
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceRoot}",
                "${workspaceRoot}/libraries/**",
                "${env:arduino.path}/tools/**",
                "${env:arduino.avr.include.path}/variants/**",
                "${env:arduino.avr.include.path}/libraries/SPI/src/",
                "${env:arduino.avr.include.path}/libraries/Wire/src/",
                "${env:arduino.avr.include.path}/cores/arduino/",
                "${env:arduino.avr.include.path}/**"
            ],
            "forcedInclude": [
                "${arduino.avr.include.path}/cores/arduino/Arduino.h"
            ],
            "intelliSenseMode": "gcc-x64",
            "compilerPath": "${env:arduino.avr.compiler.path} -std=gnu++11 -mmcu=atmega328p",
            "cStandard": "c11",
            "cppStandard": "c++11",
            "browse": {
                "path": [
                    "${workspaceRoot}/playground"
                ]
            },
            "defines": [
                "USBCON",
                "ARDUINO=10800"
            ]
        }
    ],
    "version": 4
}
```

## Libraries

We have some `libraries`, that we provide within this repository. They are
currently not available or compatible with the provided packages from the
arduino library installer.

For example, `EPD` exists inside the Arduino library, but does not have all
needed methods. Hence, we downloaded one from
[Waveshare](https://www.waveshare.com) and used that directly. In addition, we
had to alter that library because the original one used key-insensitive paths
which caused a "file not found" error on Linux.

**Resources**
- Example code of all [e-papers by Waveshare](https://github.com/waveshare/e-Paper)
- How to [create new fonts](https://wavesharejfs.blogspot.com/2018/08/make-new-larger-font-for-waveshare-spi.html)
- E-Paper Shield on Waveshare: [wiki](https://www.waveshare.com/wiki/E-Paper_Shield), [manual (pdf)](/E-Paper_Shield_User_Manual_en.pdf), and [demo code](/playground/waveshare-democode)

