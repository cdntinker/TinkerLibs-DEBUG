#ifndef Tinker_DEBUG_H
#define Tinker_DEBUG_H

// Stuff only needed in DEBUG_functions.cpp goes here.

// #include <NOTARDUINO.h>
#include <Arduino.h>

#if defined(ESP8266)
    #include <ESP8266WiFi.h>
#elif defined(ESP32)
    #include <rom/rtc.h>
    #include <WiFi.h>
#endif

extern const char *DeviceNotes;
// int DEBUG_Width = 98;
// char DEBUGtxt[92];

extern int DEBUG_Width;
extern int Line_width;
extern char DEBUGtxt[];

#define ST(A) #A
#define STR(A) ST(A)

// Function declarations


void setup_DEBUG();

void DEBUG_Title(void);
void DEBUG_Ready();
void DEBUG_Separator();
void DEBUG_SectionTitle(const char *Title);
void DEBUG_LineOut(const char *Line);
void DEBUG_LineOut2(const char *Line);

void DEBUG_BlockOut(const char *Block);

void DEBUG_Success(const char *Line);
void DEBUG_Trouble(const char *Line);
void DEBUG_Event(const char *Line);

int DEBUG_ProgressBar(int dotcount, char Dot);
void DEBUG_ProgressBar2(int dotcount);

void DEBUG_Reset();
String return_reset_reason(uint8_t reason);

void DEBUG_Init(const char *InitPart);
void DEBUG_Done(const char *InitPart);

void DEBUG_ESP_info();
void DEBUG_WiFi_info();

void DEBUG_WiFi_Mode();
void DEBUG_Wifi(const char *InitPart);
// void DEBUG_IP(const char *InitPart);
void DEBUG_IP();
void DEBUG_MAC(const char *InitPart);
void DEBUG_rssi(const char *InitPart);

#endif // Tinker_DEBUG_H
