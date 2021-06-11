// #include <NOTARDUINO.h>
#include <Arduino.h>

int DEBUG_Width = 66;

char DEBUGtxt[48];

#ifdef DEBUG // If DEBUG is turned on in platformio.ini

#include "Tinker_DEBUG.h"

// #if defined(ESP8266)
// #elif defined(ESP32)
// #include <rom/rtc.h>
// #endif
// String return_reset_reason(uint8_t reason);

// extern const char *DeviceNotes;

// #define ST(A) #A
// #define STR(A) ST(A)

void setup_DEBUG()
{
    Serial.begin(115200);
    delay(2000); // There has GOT to be a better way!!!
}

void DEBUG_Reset()
{
#if defined(ESP8266)
    sprintf(DEBUGtxt,
            "Reset Reason: %s",
            ESP.getResetReason().c_str());
    DEBUG_SectionTitle(DEBUGtxt);
#elif defined(ESP32)
    sprintf(DEBUGtxt,
            "CPU0 reset reason:  %d - %s",
            rtc_get_reset_reason(0),
            return_reset_reason(rtc_get_reset_reason(0)).c_str());
    DEBUG_SectionTitle(DEBUGtxt);
    sprintf(DEBUGtxt,
            "CPU1 reset reason:  %d - %s",
            rtc_get_reset_reason(1),
            return_reset_reason(rtc_get_reset_reason(1)).c_str());
    DEBUG_SectionTitle(DEBUGtxt);
#endif
}

void DEBUG_Init(const char *InitPart)
{
    DEBUG_Separator();
    Serial.printf("| Initialising: %-48s |\n", InitPart);
}

void DEBUG_Title()
{
    Serial.printf("\n\n#================================================================#\n");
    // Serial.printf("# %-46s #\n", DeviceTitle);
    // Serial.printf("# %-46s #\n", DeviceDescription);
    Serial.printf("# %-62s #\n", STR(DeviceName));
    Serial.printf("# %-62s #\n", STR(DeviceType));
    Serial.printf("+----------------------------------------------------------------+");
    Serial.println(DeviceNotes);
    Serial.printf("#================================================================#\n");
}

void DEBUG_Ready()
{
    Serial.printf("#================================================================#\n");
    Serial.printf("#                         Ready To Run.                          #\n");
    Serial.printf("#================================================================#\n");
}

void DEBUG_Separator()
{
    Serial.printf(">----------------------------------------------------------------<\n");
}

void DEBUG_SectionTitle(const char *Title)
{
    Serial.printf("| %-62s |\n", Title);
}

void DEBUG_LineOut(const char *Line)
{
    Serial.printf("|    %-59s |\n", Line);
}

void DEBUG_BlockOut(const char *Block)
{
    Serial.println("DEBUG_BlockOut Print:");
    Serial.printf(Block);
}

void DEBUG_Trouble(const char *Line)
{
    Serial.printf("* %-62s *\n", Line);
}

void DEBUG_Success(const char *Line)
{
    Serial.printf("+ %-62s +\n", Line);
}

int DEBUG_ProgressBar(int dotcount)
{

    if (dotcount == 0)
        Serial.printf("| ");
    Serial.printf(".");
    if (dotcount == (DEBUG_Width - 5))
    {
        Serial.printf(" |\n");
        return 0;
    }
    dotcount++;
    return (dotcount);
}

void DEBUG_ProgressBar2(int dotcount)
{
    for (int i = 0; i < (63 - dotcount); i++)
    {
        Serial.printf(" ");
    }
    Serial.printf("|\n");
}

// void debug_ESP_info()
// {
//     char Line[46];
//     // Check and report on the flash memory on this board
//     debug_SectionTitle("Board flash memory Info");
//     uint32_t realSize = ESP.getFlashChipRealSize();
//     uint32_t ideSize = ESP.getFlashChipSize();
//     FlashMode_t ideMode = ESP.getFlashChipMode();
//     sprintf(Line, "Flash real id:   %08X", ESP.getFlashChipId());
//     debug_LineOut(Line);
//     sprintf(Line, "Flash real size: %u", realSize);
//     debug_LineOut(Line);
//     sprintf(Line, "Flash real size: %u MB", realSize / 1024 / 1024);
//     debug_LineOut(Line);
//     sprintf(Line, "Flash ide  size: %u", ideSize);
//     debug_LineOut(Line);
//     sprintf(Line, "Flash ide speed: %u", ESP.getFlashChipSpeed());
//     debug_LineOut(Line);
//     sprintf(Line, "Flash ide mode:  %s", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT"
//                                                                   : ideMode == FM_DIO    ? "DIO"
//                                                                   : ideMode == FM_DOUT   ? "DOUT"
//                                                                                          : "UNKNOWN"));
//     debug_LineOut(Line);
//     if (ideSize != realSize)
//     {
//         sprintf(Line, "Flash Chip configuration wrong!");
//     }
//     else
//     {
//         sprintf(Line, "Flash Chip configuration ok.");
//     }
//     debug_LineOut(Line);
// }

#else // If DEBUG is NOT turned on in platformio.ini
void setup_DEBUG() {}
void DEBUG_Reset() {}
void DEBUG_Init(const char *InitPart) {}
void DEBUG_Title() {}
void DEBUG_Ready() {}
void DEBUG_Separator() {}
void DEBUG_SectionTitle(const char *Title) {}
void DEBUG_LineOut(const char *Line) {}
void DEBUG_Trouble(const char *Line) {}
void DEBUG_Success(const char *Line) {}
void DEBUG_ProgressBar0() {}
void DEBUG_ProgressBar1() {}
void DEBUG_ProgressBar2(int dotcount) {}

#endif // DEBUG
