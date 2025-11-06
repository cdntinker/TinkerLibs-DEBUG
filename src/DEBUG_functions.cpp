#define DEBUG
// #include <NOTARDUINO.h>
#include <Arduino.h>

// extern int DEBUG_Width;
// extern char DEBUGtxt[];

// #define DEBUGwidth 90

#ifdef DEBUGwidth
int DEBUG_Width = DEBUGwidth;
#else
int DEBUG_Width = 100;
#endif

int Line_width = DEBUG_Width - 6;
char DEBUGtxt[101];

#include <Tinker_DEBUG.h>

void debug_MakeDivider(char End, char Bar)
{
    char TheLine[111] = "";

    memset(TheLine, Bar, sizeof(TheLine) - 1);

    TheLine[0] = End;
    TheLine[DEBUG_Width] = End;
    TheLine[DEBUG_Width + 1] = '\0';

    Serial.println(TheLine);
}

void debug_CentredText(char End, const char *Text)
{
    char TheLine[111] = "";

    memset(TheLine, ' ', sizeof(TheLine) - 1);

    int TextLength = strlen(Text);
    int MidPoint = DEBUG_Width / 2;
    int StartPoint = MidPoint - (TextLength / 2);

    TheLine[0] = End;
    TheLine[DEBUG_Width] = End;
    TheLine[DEBUG_Width + 1] = '\0';

    for (int i = 0; i < TextLength; i++)
    {
        TheLine[StartPoint + i] = Text[i];
    }

    Serial.println(TheLine);
}

void debug_LeftText(char End, int Indent, const char *Text)
{

    char TheLine[111] = "";

    memset(TheLine, ' ', sizeof(TheLine) - 1);

    int TextLength = strlen(Text);

    TheLine[0] = End;
    TheLine[DEBUG_Width] = End;
    TheLine[DEBUG_Width + 1] = '\0';

    for (int i = 0; i < TextLength; i++)
    {
        TheLine[Indent + 2 + i] = Text[i];
    }

    Serial.println(TheLine);
}

void setup_DEBUG()
{
    Serial.begin(115200);
    delay(2000); // There has GOT to be a better way!!!
    Serial.println();
    Serial.println();
}

#ifdef DEBUG // If DEBUG is turned on in platformio.ini

/**/
////////////////////////////////////////////////////////////////
//                     BREAKING CHANGE!!!                     //
////////////////////////////////////////////////////////////////
// Changed `DeviceNotes` output to use `DEBUG_BlockOut()
//      will still function properly, but will require that you
//      change the format of this variable.
//      (normally defined in your project)
//
// Future thing(s): maybe figure out a good way to change the
//                  vertical borders back to `#`s
void DEBUG_Title()
{
    debug_MakeDivider('#', '=');

#ifdef FIRMWAREVERSION
    sprintf(DEBUGtxt, "%s (v%s)", STR(DeviceName), STR(FIRMWAREVERSION));
    debug_CentredText('#', DEBUGtxt);
#else
    debug_CentredText('#', STR(DeviceName));
#endif

    debug_CentredText('#', STR(DeviceType));

    debug_MakeDivider('#', '-');

    DEBUG_BlockOut(DeviceNotes);

    debug_MakeDivider('#', '=');
}

String HR_reset_reason(uint8_t reason)
{
    switch (reason)
    {
    case 1:
        return ("POWERON_RESET");
        break; /**<1, Vbat power on reset*/
    case 3:
        return ("SW_RESET");
        break; /**<3, Software reset digital core*/
    case 4:
        return ("OWDT_RESET");
        break; /**<4, Legacy watch dog reset digital core*/
    case 5:
        return ("DEEPSLEEP_RESET");
        break; /**<5, Deep Sleep reset digital core*/
    case 6:
        return ("SDIO_RESET");
        break; /**<6, Reset by SLC module, reset digital core*/
    case 7:
        return ("TG0WDT_SYS_RESET");
        break; /**<7, Timer Group0 Watch dog reset digital core*/
    case 8:
        return ("TG1WDT_SYS_RESET");
        break; /**<8, Timer Group1 Watch dog reset digital core*/
    case 9:
        return ("RTCWDT_SYS_RESET");
        break; /**<9, RTC Watch dog Reset digital core*/
    case 10:
        return ("INTRUSION_RESET");
        break; /**<10, Instrusion tested to reset CPU*/
    case 11:
        return ("TGWDT_CPU_RESET");
        break; /**<11, Time Group reset CPU*/
    case 12:
        return ("SW_CPU_RESET");
        break; /**<12, Software reset CPU*/
    case 13:
        return ("RTCWDT_CPU_RESET");
        break; /**<13, RTC Watch dog Reset CPU*/
    case 14:
        return ("EXT_CPU_RESET");
        break; /**<14, for APP CPU, reseted by PRO CPU*/
    case 15:
        return ("RTCWDT_BROWN_OUT_RESET");
        break; /**<15, Reset when the vdd voltage is not stable*/
    case 16:
        return ("RTCWDT_RTC_RESET");
        break; /**<16, RTC Watch dog reset digital core and rtc module*/
    default:
        return ("NO_MEAN");
    }
}

/**/
void DEBUG_Reset()
{
    DEBUG_Separator();

#if defined(ESP8266)
    sprintf(DEBUGtxt,
            "Reset Reason: %s",
            ESP.getResetReason().c_str());
    debug_LeftText('|', 0, DEBUGtxt);
#elif defined(ESP32)
    sprintf(DEBUGtxt,
            "CPU0 reset reason:  %d - %s",
            rtc_get_reset_reason(0),
            HR_reset_reason(rtc_get_reset_reason(0)).c_str());
    debug_LeftText('|', 0, DEBUGtxt);
    sprintf(DEBUGtxt,
            "CPU1 reset reason:  %d - %s",
            rtc_get_reset_reason(1),
            HR_reset_reason(rtc_get_reset_reason(1)).c_str());
    debug_LeftText('|', 0, DEBUGtxt);

#endif
}

/**/
void DEBUG_Init(const char *InitPart)
{
    char TheLine[111] = "";

    debug_MakeDivider('+', '-');
    sprintf(TheLine, "Init: %s", InitPart);
    debug_LeftText('|', 0, TheLine);
}

/**/
void DEBUG_Done(const char *InitPart)
{
    char TheLine[111] = "";

    sprintf(TheLine, "Done: %s", InitPart);
    debug_LeftText('|', 0, TheLine);
    debug_MakeDivider('+', '-');
}

/**/
void DEBUG_Ready()
{
    debug_MakeDivider('#', '=');
    debug_CentredText('#', "Device Running");
    debug_MakeDivider('#', '=');
}

/**/
void DEBUG_Separator()
{
    debug_MakeDivider('+', '-');
}

void DEBUG_ReAlign()
{
    Serial.println();
}

/**/
void DEBUG_SectionTitle(const char *Title)
{
    debug_MakeDivider('+', '-');
    debug_LeftText('|', 0, Title);
}

/**/
void DEBUG_LineOut(const char *Line)
{
    debug_LeftText('|', 2, Line);
}

/**/
void DEBUG_LineOut2(const char *Line)
{
    debug_LeftText('|', 4, Line);
}

/**/
void DEBUG_Trouble(const char *Line)
{
    char TheLine[111] = "";

    memset(TheLine, ' ', sizeof(TheLine) - 1);

    TheLine[0] = '+';
    TheLine[1] = 'X';
    TheLine[2] = 'X';
    TheLine[DEBUG_Width - 2] = 'X';
    TheLine[DEBUG_Width - 1] = 'X';
    TheLine[DEBUG_Width] = '+';
    TheLine[DEBUG_Width + 1] = '\0';

    for (size_t i = 0; i < strlen(Line); i++)
    {
        TheLine[i + 6] = Line[i];
    }

    Serial.println(TheLine);
}

/**/
void DEBUG_Success(const char *Line)
{
    char TheLine[111] = "";

    memset(TheLine, ' ', sizeof(TheLine) - 1);

    TheLine[0] = '+';
    TheLine[1] = '+';
    TheLine[2] = '+';
    TheLine[DEBUG_Width - 2] = '+';
    TheLine[DEBUG_Width - 1] = '+';
    TheLine[DEBUG_Width] = '+';
    TheLine[DEBUG_Width + 1] = '\0';

    for (size_t i = 0; i < strlen(Line); i++)
    {
        TheLine[i + 6] = Line[i];
    }

    Serial.println(TheLine);
}

/**/
void DEBUG_Event(const char *Line)
{
    char TheLine[111] = "";

    memset(TheLine, ' ', sizeof(TheLine) - 1);

    TheLine[0] = '+';
    TheLine[1] = '-';
    TheLine[2] = '>';
    TheLine[DEBUG_Width - 2] = '<';
    TheLine[DEBUG_Width - 1] = '-';
    TheLine[DEBUG_Width] = '+';
    TheLine[DEBUG_Width + 1] = '\0';

    for (size_t i = 0; i < strlen(Line); i++)
    {
        TheLine[i + 6] = Line[i];
    }

    Serial.println(TheLine);
}

/* This needs much work to de-duplicate code... */
//////////////////////////////////////////////////////////////
// NOTE:
// In order to insert a blank line in your text block, place
// `\n\n` where you want the blank line to appear.
//////////////////////////////////////////////////////////////
void DEBUG_BlockOut(const char *Block)
{
    int last_space = 0;
    int counter = 0;
    int Column = 0;
    int LineNum = 0;

    int Line_Width = DEBUG_Width - 6;

    char Line[DEBUG_Width];

    for (int current = 0; Block[current] != '\0'; current++, counter++, Column++)
    {
        if (isspace(Block[current])) // TODO: Add other delimiters here
            last_space = current;

        Line[Column] = Block[current];
        Line[Column + 1] = '\0'; // We're re-using Line, ensure it ends...

        if ((counter >= Line_Width) || (Block[current] == '\n'))
        {
            Line[Column - (current - last_space)] = '\0';

            counter = 0;
            current = last_space; // Loop back to before the partial word...
            Column = -1;          // Back 1 past the start because the loop will bump it one...
            LineNum++;

            if ((LineNum == 1) && (strlen(Line) == 0))
            {
            }
            else
                debug_LeftText('|', 2, Line);
        }
    }

    if (counter > 1)
        debug_LeftText('|', 2, Line);
}

/**/
int DEBUG_ProgressBar(int dotcount, char Dot)
{
    int Width = DEBUG_Width - 3;
    int dotposition = dotcount;
    int rowcount = dotcount / Width;

    dotposition = dotcount - ((Width * rowcount));

    if (dotposition == 0)
        Serial.printf("| ");

    Serial.print(Dot);
    // Serial.print(rowcount);

    if (dotposition == Width - 1)
    {
        Serial.printf(" |\n");
        return 0;
    }
    dotcount++;
    return (dotposition);
}

/**/
void DEBUG_ProgressBar2(int dotcount)
{
    for (int i = 0; i < ((DEBUG_Width - 3) - dotcount); i++)
    {
        Serial.printf(" ");
    }
    Serial.printf("|\n");
}

// Hardware & platform information
void DEBUG_ESP_info()
{
    char Line[111];
    char CoreVer[12];
    char ChipRevC[32];

#if defined(ESP8266)
    const uint32_t efuse_blocks[4]{
        READ_PERI_REG(0x3ff00050),
        READ_PERI_REG(0x3ff00054),
        READ_PERI_REG(0x3ff00058),
        READ_PERI_REG(0x3ff0005c)};

    bool is_esp8285 = ((efuse_blocks[0] & (1 << 4)) || (efuse_blocks[2] & (1 << 16)));

    // const char *ChipModel = "Dunno"; // Don't actually know
    const char *ChipModel;
    if (is_esp8285)
    {
        ChipModel = "ESP8285";
    }
    else
    {
        ChipModel = "ESP8266";
    }
    // double ChipRev = 0; // Don't actually know
    strcpy(ChipRevC, "NoClue");
    uint32_t ChipID = ESP.getChipId();
    uint32_t ChipCores = 1;
    uint32_t FlashID = ESP.getFlashChipId();
    uint32_t RAMsize = 0; // Don't actually know
    sprintf(CoreVer, "%s", ESP.getCoreVersion().c_str());
    uint32_t ideMode = ESP.getFlashChipMode();
#elif defined(ESP32)
    const char *ChipModel = ESP.getChipModel();
    // uint32_t ChipRev = ESP.getChipRevision();
    sprintf(ChipRevC, "%f", ESP.getChipRevision());
    // ChipRevC[3] = '\0';
    uint32_t ChipID = 0; // ESP efuse ID
    for (int i = 0; i < 17; i = i + 8)
    {
        ChipID |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    uint32_t ChipCores = ESP.getChipCores();
    uint32_t FlashID = 000; // Don't actually know
    uint32_t PSramSize = ESP.getPsramSize();
    uint32_t RAMsize = ESP.getHeapSize();
    sprintf(CoreVer, "%d.%d.%d", ESP_ARDUINO_VERSION_MAJOR, ESP_ARDUINO_VERSION_MINOR, ESP_ARDUINO_VERSION_PATCH);
    uint32_t ideMode = 4;
#endif
    const char *SDKver = ESP.getSdkVersion();
    uint32_t FlashChipSize = ESP.getFlashChipSize();
    uint32_t FlashSpeed = ESP.getFlashChipSpeed();
    uint32_t FreeHeap = ESP.getFreeHeap();

    DEBUG_SectionTitle("ESP Info");

    // sprintf(Line, "  ESP Chip model : %s Rev %.1f", ChipModel, ChipRev);
    sprintf(Line, "  ESP Chip model : %s Rev %s", ChipModel, ChipRevC);
    DEBUG_LineOut(Line);
    sprintf(Line, "         Chip ID : %08X", ChipID);
    DEBUG_LineOut(Line);
    sprintf(Line, " Number of Cores : %d", ChipCores);
    DEBUG_LineOut(Line);
#if defined(ESP8266)
    sprintf(Line, "   Flash Chip ID : %08X", FlashID);
    DEBUG_LineOut(Line);
#elif defined(ESP32)
    DEBUG_LineOut("   Flash Chip ID : No way to retrieve");
#endif
    sprintf(Line, "      Flash Size : %d (%.3f MB)", FlashChipSize, FlashChipSize / 1024.0 / 1024.0);
    DEBUG_LineOut(Line);
    sprintf(Line, "     Flash speed : %u MHz", FlashSpeed / 1000 / 1000);
    DEBUG_LineOut(Line);
#if defined(ESP32)
    sprintf(Line, "      Psram Size : %d (%.3f MB)", PSramSize, PSramSize / 1024.0 / 1024.0);
    DEBUG_LineOut(Line);
#endif
    sprintf(Line, "        Ram Size : %d (%.3f KB)", RAMsize, RAMsize / 1024.0); // / 1024.0);
    DEBUG_LineOut(Line);
    sprintf(Line, "       Free heap : %d (%.3f KB)", FreeHeap, FreeHeap / 1024.0); // / 1024.0);
    DEBUG_LineOut(Line);
    sprintf(Line, " Arduino version : %s", CoreVer);
    DEBUG_LineOut(Line);
    sprintf(Line, " ESP SDK version : %s", SDKver);
    DEBUG_LineOut(Line);
    sprintf(Line, "  Flash ide mode : %s", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT"
                                                                    : ideMode == FM_DIO    ? "DIO"
                                                                    : ideMode == FM_DOUT   ? "DOUT"
                                                                                           : "BORKED"));
    DEBUG_LineOut(Line);
    DEBUG_Separator();
}

////////////////////////////////////////////////////////////////
//                   WiFi Related Debugging                   //
////////////////////////////////////////////////////////////////
extern char APssid[];
extern char APpass[];

void DEBUG_WiFi_info()
{
    // Serial.println("-=[WIP]=-");
    char WiFi_Statii[][32] =
        {
            "WL_IDLE_STATUS",
            "WL_NO_SSID_AVAIL",
            "__2__",
            "WL_CONNECTED",
            "WL_CONNECT_FAILED",
            "__5__",
            "WL_WRONG_PASSWORD",
            "WL_DISCONNECTED"};

    char WiFiMODE[8] = "-----";
    char WiFiSSID[32] = "____________";
    char WiFiPASS[32] = "____________";
    long WiFiRSSI = WiFi.RSSI();
    char WiFiHOST[32] = "____________";
    char WiFiMAC[24] = "__:__:__:__:__:__:__:__";
    char WiFiIP[16] = "___.___.___.___";

    char WiFiIP2[16] = "___.___.___.___";
    char WiFiSSID2[32] = "____________";
    char WiFiPASS2[32] = "____________";
    int WiFiClients = 0;

    const char *WiFi_MODES[] = {"NULL", "STA", "AP", "STA+AP"};
    strcpy(WiFiMODE, WiFi_MODES[WiFi.getMode()]);

    if (strcmp(WiFiMODE, "STA") == 0)
    {
        if (strcmp(WiFi.localIP().toString().c_str(), "0.0.0.0") == 0)
            strcpy(WiFiIP, "(IP unset)");
        else
            strcpy(WiFiIP, WiFi.localIP().toString().c_str());

        if (strlen(WiFi.SSID().c_str()) != 0)
            strcpy(WiFiSSID, WiFi.SSID().c_str());
        else
            strcpy(WiFiSSID, "(SSID unset)");
    }
    else if (strcmp(WiFiMODE, "AP") == 0)
    {
        strcpy(WiFiIP2, WiFi.softAPIP().toString().c_str());
        strcpy(WiFiSSID2, APssid);
        strcpy(WiFiPASS2, APpass);
        WiFiClients = WiFi.softAPgetStationNum();
    }
    else if (strcmp(WiFiMODE, "STA+AP") == 0)
    {
        if (strcmp(WiFi.localIP().toString().c_str(), "0.0.0.0") == 0)
            strcpy(WiFiIP, "(IP unset)");
        else
            strcpy(WiFiIP, WiFi.localIP().toString().c_str());

        if (strlen(WiFi.SSID().c_str()) != 0)
            strcpy(WiFiSSID, WiFi.SSID().c_str());
        else
            strcpy(WiFiSSID, "(SSID unset)");

        strcpy(WiFiIP2, WiFi.softAPIP().toString().c_str());
        strcpy(WiFiSSID2, APssid);
        strcpy(WiFiPASS2, APpass);
        WiFiClients = WiFi.softAPgetStationNum();
    }
    else
    {
        strcpy(WiFiIP, "(dunno)");
        strcpy(WiFiSSID, "(dunno)");
    }

    strcpy(WiFiHOST, WiFi.getHostname());

#if defined(ESP8266)

    // #include <ESP8266WiFi.h>
    strcpy(WiFiMAC, WiFi.macAddress().c_str());
#elif defined(ESP32)

    // #include <WiFi.h>
    uint8_t baseMac[6];
    // Get MAC address for WiFi station
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
    char baseMacChr[18] = {0};
    sprintf(WiFiMAC,
            "%02X:%02X:%02X:%02X:%02X:%02X",
            baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
#endif

    DEBUG_SectionTitle("WiFi Info");

    sprintf(DEBUGtxt, "      Connected? : %s", WiFi.isConnected() ? "YES" : "NO");
    DEBUG_LineOut(DEBUGtxt);

    sprintf(DEBUGtxt, "          Status : %d - %s", WiFi.status(), (WiFi.status() == 255) ? "Not Connected" : WiFi_Statii[WiFi.status()]);
    DEBUG_LineOut(DEBUGtxt);

    sprintf(DEBUGtxt, "            Mode : %s", WiFiMODE);
    DEBUG_LineOut(DEBUGtxt);

    if ((strcmp(WiFiMODE, "STA") == 0) || (strcmp(WiFiMODE, "STA+AP") == 0))
    {
        DEBUG_LineOut("STA:");

        sprintf(DEBUGtxt, "            SSID : %s", WiFiSSID);
        DEBUG_LineOut(DEBUGtxt);

        sprintf(DEBUGtxt, "            PASS : %s", WiFiPASS);
        DEBUG_LineOut(DEBUGtxt);

        sprintf(DEBUGtxt, "            RSSI : %ld dBm", WiFiRSSI);
        DEBUG_LineOut(DEBUGtxt);

        sprintf(DEBUGtxt, "        HostName : %s", WiFiHOST);
        DEBUG_LineOut(DEBUGtxt);

        sprintf(DEBUGtxt, "             MAC : %s", WiFiMAC);
        DEBUG_LineOut(DEBUGtxt);

        sprintf(DEBUGtxt, "      IP address : %s", WiFiIP);
        DEBUG_LineOut(DEBUGtxt);
    }

    if ((strcmp(WiFiMODE, "AP") == 0) || (strcmp(WiFiMODE, "STA+AP") == 0))
    {
        DEBUG_LineOut("AP:");

        sprintf(DEBUGtxt, "            SSID : %s", WiFiSSID2);
        DEBUG_LineOut(DEBUGtxt);

        sprintf(DEBUGtxt, "            PASS : %s", WiFiPASS2);
        DEBUG_LineOut(DEBUGtxt);

        sprintf(DEBUGtxt, "      IP address : %s", WiFiIP2);
        DEBUG_LineOut(DEBUGtxt);

        sprintf(DEBUGtxt, "         Clients : %d", WiFiClients);
        DEBUG_LineOut(DEBUGtxt);
    }

//////
#ifdef DEBUGx
    debug_CentredText('|', "- - - - - - - - - -");

    sprintf(DEBUGtxt, "      subnetMask : %s", WiFi.subnetMask().toString().c_str());
    DEBUG_LineOut(DEBUGtxt);
    sprintf(DEBUGtxt, "       gatewayIP : %s", WiFi.gatewayIP().toString().c_str());
    DEBUG_LineOut(DEBUGtxt);
    sprintf(DEBUGtxt, "          dnsIP 0: %s", WiFi.dnsIP(0).toString().c_str());
    DEBUG_LineOut(DEBUGtxt);
    sprintf(DEBUGtxt, "          dnsIP 1: %s", WiFi.dnsIP(1).toString().c_str());
    DEBUG_LineOut(DEBUGtxt);
    sprintf(DEBUGtxt, "      broadcastIP: %s", WiFi.broadcastIP().toString().c_str());
    DEBUG_LineOut(DEBUGtxt);
#endif
    //////
    DEBUG_Separator();
}

////  (likely obsolete...) /////
void DEBUG_WiFi_Mode()
{
    const char *WiFi_MODES[] = {"NULL", "STA", "AP", "STA+AP"};

    Serial.printf("|          MODE : %-81s |\n", WiFi_MODES[WiFi.getMode()]);
}

/////  Austin's Additions  /////
////  (likely obsolete...) /////
void DEBUG_Wifi(const char *InitPart)
{
    // Serial.printf("|          SSID : %-87s |\n", InitPart);
    Serial.printf("|          SSID : %-81s |\n", InitPart);
}

////  (likely obsolete...) /////
void DEBUG_IP()
{
    Serial.printf("|    IP address : %-81s |\n", WiFi.localIP().toString().c_str());
}

////  (likely obsolete...) /////
void DEBUG_MAC(const char *InitPart)
{
    Serial.printf("|    MAC address : %-83s |\n", InitPart);
}

////  (likely obsolete...) /////
void DEBUG_rssi(const char *InitPart)
{
    Serial.printf("|    RSSI : %-87s |\n", InitPart);
}

////////////////////////////////////////////////////////////////
//                       TO BE CREATED                        //
////////////////////////////////////////////////////////////////
// DEBUG_MQTT_info
// DEBUG_Bluetooth_info
// DEBUG_Ethernet_info
// DEBUG_FS_info
// DEBUG_GPIO_info

#else // If DEBUG is NOT turned on in platformio.ini
// void setup_DEBUG() {}
void DEBUG_Reset() {}
void DEBUG_Init(const char *InitPart) {}
void DEBUG_Done(const char *InitPart) {}
void DEBUG_Title() {}
void DEBUG_Ready() {}
void DEBUG_ReAlign() {}
void DEBUG_Separator() {}
void DEBUG_SectionTitle(const char *Title) {}
void DEBUG_LineOut(const char *Line) {}
void DEBUG_LineOut2(const char *Line) {}
void DEBUG_Trouble(const char *Line) {}
void DEBUG_Success(const char *Line) {}
void DEBUG_Event(const char *Line) {}
void DEBUG_BlockOut(const char *Block) {}
int DEBUG_ProgressBar(int dotcount, char Dot) { return 0; }
void DEBUG_ProgressBar2(int dotcount) {}

void DEBUG_ESP_info() {}
void DEBUG_WiFi_info() {}

/////  Austin's Additions  /////
void DEBUG_WiFi_Mode() {}
void DEBUG_Wifi(const char *InitPart) {}
// void DEBUG_IP(const char *InitPart) {}
void DEBUG_IP() {}
void DEBUG_MAC(const char *InitPart) {}
void DEBUG_rssi(const char *InitPart) {}

#endif // DEBUG

/* ************************************************************************************************************* */
#ifdef DEBUGl

void DEBUG_Lib_Init(const char *Library, const char *Message)
{
    char Line[111];
    debug_MakeDivider(':', '-');
    sprintf(Line, "{%s} - Init: %s", Library, Message);
    debug_LeftText(':', 2, Line);
}
void DEBUG_Lib_Done(const char *Library, const char *Message)
{
    char Line[111];
    sprintf(Line, "{%s} - Done: %s", Library, Message);
    debug_LeftText(':', 2, Line);
    debug_MakeDivider(':', '-');
}
void DEBUG_Lib_LineOut(const char *Library, const char *Message)
{
    char Line[111];
    sprintf(Line, "{%s} - %s", Library, Message);
    debug_LeftText(':', 2, Line);
}
void DEBUG_Lib_LineOut2(const char *Library, const char *Message)
{
    char Line[111];
    sprintf(Line, "{%s} -   %s", Library, Message);
    debug_LeftText(':', 2, Line);
}
void DEBUG_Lib_BlockOut(const char *Library, const char *Message)
{
    int last_space = 0;
    int counter = 0;
    int Column = 0;
    int LineNum = 0;

    int Line_Width = DEBUG_Width - 6;

    char Line[DEBUG_Width];

    for (int current = 0; Message[current] != '\0'; current++, counter++, Column++)
    {
        if (isspace(Message[current])) // TODO: Add other delimiters here
            last_space = current;

        Line[Column] = Message[current];
        Line[Column + 1] = '\0'; // We're re-using Line, ensure it ends...

        if ((counter >= Line_Width) || (Message[current] == '\n'))
        {
            Line[Column - (current - last_space)] = '\0';

            counter = 0;
            current = last_space; // Loop back to before the partial word...
            Column = -1;          // Back 1 past the start because the loop will bump it one...
            LineNum++;

            if ((LineNum == 1) && (strlen(Line) == 0))
            {
            }
            else
                debug_LeftText(':', 2, Line);
        }
    }

    if (counter > 1)
        debug_LeftText(':', 2, Line);
}
void DEBUG_Lib_Trouble(const char *Library, const char *Message)
{
    char TheLine[111] = "";
    memset(TheLine, ' ', sizeof(TheLine) - 1);
    {
        TheLine[0] = ':';
        TheLine[1] = 'X';
        TheLine[2] = 'X';
        TheLine[DEBUG_Width - 2] = 'X';
        TheLine[DEBUG_Width - 1] = 'X';
        TheLine[DEBUG_Width] = ':';
        TheLine[DEBUG_Width + 1] = '\0';
    }

    char Line[111] = "";

    int Position = 4;
    sprintf(Line, "{%s} - %s", Library, Message);
    for (size_t i = 0; i < strlen(Line); i++)
    {
        TheLine[Position] = Line[i];
        Position++;
    }

    Serial.println(TheLine);
}
void DEBUG_Lib_Success(const char *Library, const char *Message)
{
    char TheLine[111] = "";
    memset(TheLine, ' ', sizeof(TheLine) - 1);

    {
        TheLine[0] = ':';
        TheLine[1] = '+';
        TheLine[2] = '+';
        TheLine[DEBUG_Width - 2] = '+';
        TheLine[DEBUG_Width - 1] = '+';
        TheLine[DEBUG_Width] = ':';
        TheLine[DEBUG_Width + 1] = '\0';
    }

    char Line[111] = "";

    int Position = 4;
    sprintf(Line, "{%s} - %s", Library, Message);
    for (size_t i = 0; i < strlen(Line); i++)
    {
        TheLine[Position] = Line[i];
        Position++;
    }

    Serial.println(TheLine);
}
void DEBUG_Lib_Event(const char *Library, const char *Message)
{
    char TheLine[111] = "";
    memset(TheLine, ' ', sizeof(TheLine) - 1);

    {
        TheLine[0] = ':';
        TheLine[1] = '-';
        TheLine[2] = '>';
        TheLine[DEBUG_Width - 2] = '<';
        TheLine[DEBUG_Width - 1] = '-';
        TheLine[DEBUG_Width] = ':';
        TheLine[DEBUG_Width + 1] = '\0';
    }

    char Line[111] = "";

    int Position = 4;
    sprintf(Line, "{%s} - %s", Library, Message);
    for (size_t i = 0; i < strlen(Line); i++)
    {
        TheLine[Position] = Line[i];
        Position++;
    }

    Serial.println(TheLine);
}
int DEBUG_Lib_ProgressBar(int dotcount, char Dot)
{
    int Width = DEBUG_Width - 3;
    int dotposition = dotcount;
    int rowcount = dotcount / Width;

    dotposition = dotcount - ((Width * rowcount));

    if (dotposition == 0)
        Serial.printf(": ");

    Serial.print(Dot);
    // Serial.print(rowcount);

    if (dotposition == Width - 1)
    {
        Serial.printf(" |\n");
        return 0;
    }
    dotcount++;
    return (dotposition);
}
void DEBUG_Lib_ProgressBar2(int dotcount)
{
    for (int i = 0; i < ((DEBUG_Width - 3) - dotcount); i++)
    {
        Serial.printf(" ");
    }
    Serial.printf(":\n");
}
void DEBUG_Lib_Separator()
{
    debug_MakeDivider(':', '-');
}

#else
void DEBUG_Lib_Init(const char *Library, const char *Message) {}
void DEBUG_Lib_Done(const char *Library, const char *Message) {}
void DEBUG_Lib_LineOut(const char *Library, const char *Message) {}
void DEBUG_Lib_LineOut2(const char *Library, const char *Message) {}
void DEBUG_Lib_BlockOut(const char *Library, const char *Message) {}
void DEBUG_Lib_Success(const char *Library, const char *Message) {}
void DEBUG_Lib_Trouble(const char *Library, const char *Message) {}
void DEBUG_Lib_Event(const char *Library, const char *Message) {}
int DEBUG_Lib_ProgressBar(int dotcount, char Dot) { return 0; }
void DEBUG_Lib_ProgressBar2(int dotcount) {}
void DEBUG_Lib_Separator() {}

#endif // DEBUGl
