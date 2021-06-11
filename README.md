# LibTesting-DEBUG
Testing libraries for PlatformIO usage. (DEBUG)

# A collection of Serial Output functions.

If DEBUG is turned on in platformio.ini (build_flags = -D DEBUG), the following functions are enabled.  Otherwise, they're defined as empty functions.

`setup_DEBUG();`
    Currently, just turns on Serial output at 115200 baud.

`DEBUG_Title(void);`

`DEBUG_Ready();`

`DEBUG_Separator();`

`DEBUG_SectionTitle(const char *Title);`

`DEBUG_LineOut(const char *Line);`

`DEBUG_BlockOut(const char *Block);`

`DEBUG_Success(const char *Line);`

`DEBUG_Trouble(const char *Line);`

`DEBUG_ProgressBar0();`

`DEBUG_ProgressBar1();`

`DEBUG_ProgressBar2(int dotcount);`

`DEBUG_Reset();`

`DEBUG_Init(const char* InitPart);`
