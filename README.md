# TinkerLibs-DEBUG

- [Overview](#overview)
- Usage:
  - [With PlatformIO](#platformio)
  - [With Arduino IDE](#arduino-ide)
- [The Functions](#the-functions)
- [An Example](#an-example)

## Overview
A collection of Serial Output functions.

These functions create a neatly formatted serial debug output while developing your project.  Then, by simply NOT defining `DEBUG`, you save ~3KB of flash memory on your released version of the firmware.

If **DEBUG** is turned on in platformio.ini (`build_flags = -D DEBUG`), the following [functions](#the-functions) are enabled.  Otherwise, they're defined as empty functions.

**NOTE:**  The Arduino core libraries for ESP-32 & ESP-8266 have `Serial.printf()`.  Apparently, not so much with the Atmel core libraries.  (How silly...)

## Usage
### PlatformIO
In `platformio.ini`, add https://github.com/cdntinker/TinkerLibs-DEBUG to your `lib-deps` for the project.

```
lib_deps =
   Some Library
   https://github.com/cdntinker/TinkerLibs-DEBUG
   Some Other Library
```

Then add `#include <Tinker_DEBUG.h>` to any source file you want to reference these functions in.

### Arduino IDE
No idea...  Don't use it...

Anybody wanna work this out for me?

Well...  Here goes a try... (I installed it...)

To install this library in Arduino, You'll have to do it manually.

In your default sketch folder (`~/Arduino` on Linux), you'll find a folder named libraries.

Create a subfolder in there for this library.  (I named it `TinkerLibs-DEBUG` here.)

Download and copy the content of the `src` & `include` folders there.

You will have to go into `DEBUG_functions.cpp` and add `#define DEBUG` at the start.

Which kinda defeats the idea of being able to compile with/without the serial output easily...

## The Functions
These are all declared in **Tinker_DEBUG.h**

### `void setup_DEBUG()`
Currently, just turns on Serial output at 115200 baud.

(Does a `delay(2000)` too because Arduino's Serial code starts slow.)

### `void DEBUG_Title(void)`
Sends out a block of information about the device.

    #================================================================#
    # DeviceTitle                                                    #
    # DeviceDescription                                              #
    +----------------------------------------------------------------+
    # DeviceNotes (Notes about the device...)                        #
    #================================================================#

**DeviceTitle** & **DeviceDescription** are character strings pulled from `#define`s (probably fed in from platformio.ini)

**DeviceNotes** is a `const char*` declared elsewhere.  (This should happen before `DEBUG_Title` is called... :stuck_out_tongue_winking_eye: )

### `void DEBUG_Reset()`
Sends out the reason for the latest device restart.

Example:

    | Reset Reason: External System                                  |

(It uses the following function to get reset info if you're building for ESP32...)

### `String return_reset_reason(uint8_t reason)`

### `void DEBUG_Ready()`
Sends out a block indicating `setup()` is finished

    #================================================================#
    #                         Ready To Run.                          #
    #================================================================#

### `void DEBUG_Separator()`
Sends out a line to separate debugging information into distinct blocks.

    >----------------------------------------------------------------<

### `void DEBUG_SectionTitle(const char *Title)`
    >----------------------------------------------------------------<
    | Title                                                          |

### `void DEBUG_LineOut(const char *Line)`
    |    Line                                                        |

### `void DEBUG_Success(const char *Line)`
    + Line                                                           +

### `void DEBUG_Trouble(const char *Line)`
    * Line                                                           *

### `void DEBUG_BlockOut(const char *Block)`
Sends out a preformatted bloack of text.

(This one's a little odd...  I should probably write up a bit of a tutorial on how to set up the block.)

### `int DEBUG_ProgressBar(int dotcount, char Dot)`
Builds & Sends out a (potentially multi-line) progress bar.

    | .............................................................. |
    | .......................................                        |


`Dot` is the ASCII character to be used as the dot in the progress bar.

Usage:

    `int Foo = 0;`
    `for (int Bar = 0; Bar <= 100; Bar++)`
    `{`
    `Foo = DEBUG_ProgressBar(Foo, '.');`
    `}`
    `DEBUG_ProgressBar2(Foo);`

Foo is just a throwaway placeholder needed to track horizontal position.

The for loop is whatever process you're indicating progress for.

`DEBUG_ProgressBar2(Foo);` adds the blanks & closes out the line when the process is finished.

### `void DEBUG_ProgressBar2(int dotcount)`

### `void DEBUG_Init(const char* InitPart)`
Sends out a seperator and an indication of what's being initialised.

    >----------------------------------------------------------------<
    | Initialising: InitPart                                         |

## An Example
    #================================================================#
    # Test-8266                                                      #
    # WutEvr                                                         #
    +----------------------------------------------------------------+
    # Welcome to an example for TinkerLibs-DEBUG.                    #
    # This is the content of DeviceNotes.                            #
    #================================================================#
    >----------------------------------------------------------------<
    | Reset Reason: External System                                  |
    >----------------------------------------------------------------<
    | Initialising: Sumpin Special                                   |
    >----------------------------------------------------------------<
    | Progress Bar Test                                              |
    | .............................................................. |
    | .......................................                        |
    #================================================================#
    #                         Ready To Run.                          #
    #================================================================#

