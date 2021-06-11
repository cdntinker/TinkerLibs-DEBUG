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

**DeviceTitle** & **DeviceDescription** are character strings pulled from `#define`s (probably fed in from platformio.ini)

**DeviceNotes** is a `const char*` declared elsewhere.  (This should happen before `DEBUG_Title` is called... :stuck_out_tongue_winking_eye: )

### `DEBUG_Ready();`

### `DEBUG_Separator();`

### `DEBUG_SectionTitle(const char *Title);`

### `DEBUG_LineOut(const char *Line);`

### `DEBUG_BlockOut(const char *Block);`

### `DEBUG_Success(const char *Line);`

### `DEBUG_Trouble(const char *Line);`

### `DEBUG_ProgressBar0();`

### `DEBUG_ProgressBar1();`

### `DEBUG_ProgressBar2(int dotcount);`

### `DEBUG_Reset();`

    Sends out the reason for the latest device restart.

### `DEBUG_Init(const char* InitPart);`
