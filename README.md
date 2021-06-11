# LibTesting-DEBUG
Testing libraries for PlatformIO usage. (DEBUG)

# A collection of Serial Output functions.

If **DEBUG** is turned on in platformio.ini (`build_flags = -D DEBUG`), the following functions are enabled.  Otherwise, they're defined as empty functions.

These are all declared in **Tinker_DEBUG.h**

### `setup_DEBUG();`

Currently, just turns on Serial output at 115200 baud.

(Does a `delay(2000)` too because Arduino's Serial code starts slow.)

### `DEBUG_Title(void);`

Sends out a block of information about the device.

    #================================================================#
    # DeviceTitle                                                    #
    # DeviceDescription                                              #
    +----------------------------------------------------------------+
    # DeviceNotes (Notes about the device...)                        #
    #================================================================#

**DeviceTitle** & **DeviceDescription** are character strings pulled from `#define`s (probably fed in from platformio.ini)

**DeviceNotes** is a `const char*` declared elsewhere.  (This should happen before `DEBUG_Title` is called... :stuck_out_tongue_winking_eye: )

### `DEBUG_Reset();`

    Sends out the reason for the latest device restart.

Example:

    | Reset Reason: External System                                  |

### `DEBUG_Ready();`

Sends out a block indicating `setup()` is finished

    #================================================================#
    #                         Ready To Run.                          #
    #================================================================#

### `DEBUG_Separator();`

Sends out a line to separate debugging information into distinct blocks.

    >----------------------------------------------------------------<

### `DEBUG_SectionTitle(const char *Title);`

    | Title                                                          |

### `DEBUG_LineOut(const char *Line);`

    |    Line                                                        |

### `DEBUG_Success(const char *Line);`

    + Line                                                           +

### `DEBUG_Trouble(const char *Line);`

    * Line                                                           *

### `DEBUG_BlockOut(const char *Block);`

Sends out a preformatted bloack of text.

(This one's a little odd...  I should probably write up a bit of a tutorial on how to set up the block.)

### `DEBUG_ProgressBar0();`

### `DEBUG_ProgressBar1();`

### `DEBUG_ProgressBar2(int dotcount);`

### `DEBUG_Init(const char* InitPart);`
