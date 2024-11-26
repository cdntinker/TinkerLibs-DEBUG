// #include <NOTARDUINO.h>
#include <Arduino.h>

int DEBUG_Width = 98;

char DEBUGtxt[92];

#ifdef DEBUG // If DEBUG is turned on in platformio.ini

#include <Tinker_DEBUG.h>


void setup_DEBUG()
{
    Serial.begin(115200);
    delay(2000); // There has GOT to be a better way!!!
    Serial.println();
    Serial.println();
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
DEBUG_Separator();

#if defined(ESP8266)
    sprintf(DEBUGtxt,
            "Reset Reason: %s",
            ESP.getResetReason().c_str());
    Serial.printf("| %-97s |\n", DEBUGtxt);
#elif defined(ESP32)
    sprintf(DEBUGtxt,
            "CPU0 reset reason:  %d - %s",
            rtc_get_reset_reason(0),
            return_reset_reason(rtc_get_reset_reason(0)).c_str());
    Serial.printf("| %-97s |\n", DEBUGtxt);
    sprintf(DEBUGtxt,
            "CPU1 reset reason:  %d - %s",
            rtc_get_reset_reason(1),
            return_reset_reason(rtc_get_reset_reason(1)).c_str());
    Serial.printf("| %-97s |\n", DEBUGtxt);

#endif
}

void DEBUG_Init(const char *InitPart)
{
    DEBUG_Separator();
    Serial.printf("| Initialising: %-83s |\n", InitPart);
}

void DEBUG_Title()
{
    Serial.printf("\n\n#===================================================================================================#\n");
    Serial.printf("# %-97s #\n", STR(DeviceName));
    Serial.printf("# %-97s #\n", STR(DeviceType));
    Serial.printf("+---------------------------------------------------------------------------------------------------+");
    Serial.println(DeviceNotes);
    Serial.printf("#===================================================================================================#\n");
}

void DEBUG_Ready()
{
    Serial.printf("#===================================================================================================#\n");
    Serial.printf("#                                           Device Running                                          #\n");
    Serial.printf("#===================================================================================================#\n");
}

void DEBUG_Separator()
{
    Serial.printf(">---------------------------------------------------------------------------------------------------<\n");
}

void DEBUG_SectionTitle(const char *Title)
{
    DEBUG_Separator();
    Serial.printf("| %-97s |\n", Title);
}

void DEBUG_LineOut(const char *Line)
{
    Serial.printf("|    %-94s |\n", Line);
}

void DEBUG_LineOut2(const char *Line)
{
    Serial.printf("|       %-91s |\n", Line);
}

void DEBUG_BlockOut(const char *Block)
{
    Serial.println("DEBUG_BlockOut Print:");
    Serial.printf(Block);
}

void DEBUG_Trouble(const char *Line)
{
    Serial.printf("* %-97s *\n", Line);
}

void DEBUG_Success(const char *Line)
{
    Serial.printf("+ %-97s +\n", Line);
}

int DEBUG_ProgressBar(int dotcount, char Dot)
{

    if (dotcount == 0)
        Serial.printf("| ");
    Serial.print(Dot);
    if (dotcount == (DEBUG_Width - 2))
    {
        Serial.printf(" |\n");
        return 0;
    }
    dotcount++;
    return (dotcount);
}

void DEBUG_ProgressBar2(int dotcount)
{
    for (int i = 0; i < ((DEBUG_Width - 0) - dotcount); i++)
    {
        Serial.printf(" ");
    }
    Serial.printf("|\n");
}

void DEBUG_TEST_ESP_info()
{
//     char Line[46];
//     // Check and report on the flash memory on this board
//     DEBUG_SectionTitle("Board flash memory Info");
// #if defined(ESP8266)
//     FlashMode_t ideMode = ESP.getFlashChipMode();
// #elif defined(ESP32)
//         // uint32_t ideMode = ESP.getFlashChipMode();
// #endif
// #if defined(ESP8266)
//     sprintf(Line, " Flash ide mode:  %s", (ideMode == FM_QIO ? "QIO"
//                                         : ideMode == FM_QOUT ? "QOUT"
//                                         : ideMode == FM_DIO    ? "DIO"
//                                         : ideMode == FM_DOUT   ? "DOUT"
//                                         : "UNKNOWN"));
//     DEBUG_LineOut(Line);
//     // if (ideSize != realSize)
//     // {
//     //     sprintf(Line, "Flash Chip configuration wrong!");
//     // }
//     // else
//     // {
//     //     sprintf(Line, "Flash Chip configuration ok.");
//     // }
//     // DEBUG_LineOut(Line);
// #elif defined(ESP32)
//     // sprintf(Line, " Flash ide mode:  %d", ideMode);
// #endif
}

// Hardware & platform information
void DEBUG_ESP_info()
{
    char Line[46];
    char CoreVer[12];
#if defined(ESP8266)
    const char* ChipModel = "Dunno";                    // Don't actually know
    double ChipRev = 0;                                 // Don't actually know
    uint32_t ChipID =  ESP.getChipId();
    uint32_t ChipCores = 1;
    uint32_t FlashID = ESP.getFlashChipId();
    uint32_t RAMsize = 666;                             // Don't actually know
    sprintf(CoreVer, "%s", ESP.getCoreVersion().c_str());
    // const char* SDKver = ESP.getSdkVersion();
    uint32_t ideMode = ESP.getFlashChipMode();
#elif defined(ESP32)
    const char* ChipModel = ESP.getChipModel();
    uint32_t ChipRev = ESP.getChipRevision();
    uint32_t ChipID = 0;        // ESP efuse ID
        for (int i = 0; i < 17; i = i + 8)
        {
            ChipID |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
        }
    uint32_t ChipCores = ESP.getChipCores();
    uint32_t FlashID = 000;                             // Don't actually know
    uint32_t PSramSize = ESP.getPsramSize();
    uint32_t RAMsize = ESP.getHeapSize();
    sprintf(CoreVer, "%d.%d.%d", ESP_ARDUINO_VERSION_MAJOR, ESP_ARDUINO_VERSION_MINOR, ESP_ARDUINO_VERSION_PATCH);
    // const char* SDKver = ESP.getSdkVersion();
    uint32_t ideMode = 4;
#endif
    const char* SDKver = ESP.getSdkVersion();
    uint32_t FlashChipSize = ESP.getFlashChipSize();
    uint32_t FlashSpeed = ESP.getFlashChipSpeed();
    uint32_t FreeHeap = ESP.getFreeHeap();

    DEBUG_SectionTitle("ESP Info");

    // sprintf(Line, "  ESP Chip model: %s Rev %.1f", ChipModel, ChipRev);
    sprintf(Line, "  ESP Chip model: %s Rev %.1f", ChipModel, ChipRev);
    DEBUG_LineOut(Line);
    sprintf(Line, "         Chip ID: %08X",ChipID);
    DEBUG_LineOut(Line);
    sprintf(Line, " Number of Cores: %d", ChipCores);
    DEBUG_LineOut(Line);
#if defined(ESP8266)
    sprintf(Line, "   Flash Chip ID: %08X", FlashID);
    DEBUG_LineOut(Line);
#elif defined(ESP32)
    DEBUG_LineOut("   Flash Chip ID: No way to retrieve");
#endif
    sprintf(Line, "      Flash Size: %d (%.3f MB)", FlashChipSize, FlashChipSize / 1024.0 / 1024.0);
    DEBUG_LineOut(Line);
    sprintf(Line, "     Flash speed: %u MHz", FlashSpeed / 1000 / 1000);
    DEBUG_LineOut(Line);
#if defined(ESP32)
    sprintf(Line, "      Psram Size: %d (%.3f MB)", PSramSize, PSramSize / 1024.0 / 1024.0);
    DEBUG_LineOut(Line);
#endif
    sprintf(Line, "        Ram Size: %d (%.3f KB)", RAMsize, RAMsize / 1024.0);// / 1024.0);
    DEBUG_LineOut(Line);
    sprintf(Line, "       Free heap: %d (%.3f KB)", FreeHeap, FreeHeap / 1024.0);// / 1024.0);
    DEBUG_LineOut(Line);
    sprintf(Line, " Arduino version: %s", CoreVer);
    DEBUG_LineOut(Line);
    sprintf(Line, " ESP SDK version: %s", SDKver);
    DEBUG_LineOut(Line);
// #if defined(ESP8266)
    sprintf(Line, " Flash ide mode:  %s", (ideMode == FM_QIO ? "QIO"
                                        : ideMode == FM_QOUT ? "QOUT"
                                        : ideMode == FM_DIO    ? "DIO"
                                        : ideMode == FM_DOUT   ? "DOUT"
                                        : "BORKED"));
    DEBUG_LineOut(Line);
// #elif defined(ESP32)
//     // sprintf(Line, " Flash ide mode:  %d", ideMode);
// #endif
}

/////  Austin's Additions  /////
// WiFi related debugging
#if defined(ESP8266)
#elif defined(ESP32)
#endif

void DEBUG_WiFi_Mode()
{
    const char* WiFi_MODES[] = { "NULL", "STA", "AP", "STA+AP" };

    Serial.printf("|          MODE : %-81s |\n", WiFi_MODES[WiFi.getMode()]);
}

void DEBUG_Wifi(const char *InitPart)
{
    Serial.printf("|          SSID : %-87s |\n", InitPart);
}

// void DEBUG_IP(const char *InitPart)
// {
//     Serial.printf("|    IP address : %-81s |\n", InitPart);
// }

void DEBUG_IP()
{
    Serial.printf("|    IP address : %-81s |\n", WiFi.localIP().toString().c_str());
}

void DEBUG_MAC(const char *InitPart)
{
    Serial.printf("|    MAC address : %-83s |\n", InitPart);
}

void DEBUG_rssi(const char *InitPart)
{
    Serial.printf("|    RSSI : %-87s |\n", InitPart);
}

#else // If DEBUG is NOT turned on in platformio.ini
void setup_DEBUG() {}
void DEBUG_Reset() {}
void DEBUG_Init(const char *InitPart) {}
void DEBUG_Title() {}
void DEBUG_Ready() {}
void DEBUG_Separator() {}
void DEBUG_SectionTitle(const char *Title) {}
void DEBUG_LineOut(const char *Line) {}
void DEBUG_LineOut2(const char *Line) {}
void DEBUG_Trouble(const char *Line) {}
void DEBUG_Success(const char *Line) {}
int DEBUG_ProgressBar(int dotcount, char Dot) { return 0; }
void DEBUG_ProgressBar2(int dotcount) {}

void DEBUG_TEST_ESP_info() {}
void DEBUG_ESP_info() {}

/////  Austin's Additions  /////
void DEBUG_WiFi_Mode() {}
void DEBUG_Wifi(const char *InitPart) {}
// void DEBUG_IP(const char *InitPart) {}
void DEBUG_IP() {}
void DEBUG_MAC(const char *InitPart) {}
void DEBUG_rssi(const char *InitPart) {}

#endif // DEBUG
