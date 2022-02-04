#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include "enum.h"
#include "palette.h"

struct PatternSettings
{
    uint8_t        PatternBrightness;
    E_Patterns     PatternActive;
    E_Direction    PatternDirection;
    uint8_t        PatternDelay;
    E_Tail         PatternTail;
    uint8_t        PatternFadeAmount;
    E_WrapAround   PatternWrapAround;
    uint8_t        PatternBarLength;
    E_ColorUse     PatternColorUse;
    float          PatternPosition;
    unsigned long  PatternUpdate;

    PatternSettings() : PatternBrightness(64), 
                        PatternActive(CYLON), 
                        PatternDirection(FORWARD), 
                        PatternDelay(255), 
                        PatternTail(DUST), 
                        PatternFadeAmount(128), 
                        PatternWrapAround(YES), 
                        PatternBarLength(4),
                        PatternColorUse(RANDOM),
                        PatternPosition(0.0f)
    {

    }
};

class Pattern : public Palette
{
public:
  void setSettings(const PatternSettings&);
  PatternSettings getSettings();
  virtual void update(CLEDController& c) = 0;
  virtual void draw(CLEDController& c) = 0;
protected:
  PatternSettings settings;  
  unsigned long time;

  void drawBar(float position, float width, CRGB color);
  void applyTailEffect(CRGB* leds, int size);
};