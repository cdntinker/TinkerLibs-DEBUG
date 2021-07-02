#ifndef Tinker_DEBUG_H
#define Tinker_DEBUG_H

// Stuff only needed in DEBUG_functions.cpp goes here.

// #include <NOTARDUINO.h>
#include <Arduino.h>

#if defined(ESP8266)
#elif defined(ESP32)
#include <rom/rtc.h>
#endif

extern const char *DeviceNotes;

#define ST(A) #A
#define STR(A) ST(A)

#endif // Tinker_DEBUG_H

// Function declarations


void setup_DEBUG();

void DEBUG_Title(void);
void DEBUG_Ready();
void DEBUG_Separator();
void DEBUG_SectionTitle(const char *Title);
void DEBUG_LineOut(const char *Line);

void DEBUG_BlockOut(const char *Block);

void DEBUG_Success(const char *Line);
void DEBUG_Trouble(const char *Line);

int DEBUG_ProgressBar(int dotcount, char Dot);
void DEBUG_ProgressBar2(int dotcount);

void DEBUG_Reset();
String return_reset_reason(uint8_t reason);

void DEBUG_Init(const char *InitPart);
