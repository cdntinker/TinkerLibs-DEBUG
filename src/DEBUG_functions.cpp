// #include <NOTARDUINO.h>
#include <Arduino.h>

int DEBUG_Width = 66;

char DEBUGtxt[48];

#ifdef DEBUG // If DEBUG is turned on in platformio.ini

#include <Tinker_DEBUG.h>

void setup_DEBUG()
{
    Serial.begin(115200);
    delay(2000); // There has GOT to be a better way!!!
}

String return_reset_reason(uint8_t reason)
{
  switch ( reason)
  {
    case 1 : return ("POWERON_RESET");break;          /**<1, Vbat power on reset*/
    case 3 : return ("SW_RESET");break;               /**<3, Software reset digital core*/
    case 4 : return ("OWDT_RESET");break;             /**<4, Legacy watch dog reset digital core*/
    case 5 : return ("DEEPSLEEP_RESET");break;        /**<5, Deep Sleep reset digital core*/
    case 6 : return ("SDIO_RESET");break;             /**<6, Reset by SLC module, reset digital core*/
    case 7 : return ("TG0WDT_SYS_RESET");break;       /**<7, Timer Group0 Watch dog reset digital core*/
    case 8 : return ("TG1WDT_SYS_RESET");break;       /**<8, Timer Group1 Watch dog reset digital core*/
    case 9 : return ("RTCWDT_SYS_RESET");break;       /**<9, RTC Watch dog Reset digital core*/
    case 10 : return ("INTRUSION_RESET");break;       /**<10, Instrusion tested to reset CPU*/
    case 11 : return ("TGWDT_CPU_RESET");break;       /**<11, Time Group reset CPU*/
    case 12 : return ("SW_CPU_RESET");break;          /**<12, Software reset CPU*/
    case 13 : return ("RTCWDT_CPU_RESET");break;      /**<13, RTC Watch dog Reset CPU*/
    case 14 : return ("EXT_CPU_RESET");break;         /**<14, for APP CPU, reseted by PRO CPU*/
    case 15 : return ("RTCWDT_BROWN_OUT_RESET");break;/**<15, Reset when the vdd voltage is not stable*/
    case 16 : return ("RTCWDT_RTC_RESET");break;      /**<16, RTC Watch dog reset digital core and rtc module*/
    default : return ("NO_MEAN");
  }
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
    DEBUG_Separator();
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

int DEBUG_ProgressBar(int dotcount, char Dot)
{

    if (dotcount == 0)
        Serial.printf("| ");
    Serial.print(Dot);
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
int DEBUG_ProgressBar(int dotcount) { return 0; }
void DEBUG_ProgressBar2(int dotcount) {}

#endif // DEBUG
