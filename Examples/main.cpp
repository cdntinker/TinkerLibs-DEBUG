#include <Arduino.h>
#include <Tinker_DEBUG.h>

const char *DeviceNotes PROGMEM = R"rawliteral(
# Welcome to an example for TinkerLibs-DEBUG.                    #
# This is the content of DeviceNotes.                            #)rawliteral";

void setup()
{
  setup_DEBUG();
  DEBUG_Title();
  DEBUG_Reset();

  // The rest of your setup stuff goes here...
  DEBUG_Init("Sumpin Special");

  DEBUG_SectionTitle("Progress Bar Test");

  int Foo = 0;
  for (int Bar = 0; Bar <= 100; Bar++)
  {
    Foo = DEBUG_ProgressBar(Foo, ".");
    delay(50);
  }
  DEBUG_ProgressBar2(Foo);

  DEBUG_Ready();
}

void loop()
{
  // put your main code here, to run repeatedly:
}
