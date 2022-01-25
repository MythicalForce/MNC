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
};

class Pattern
{
public:
  void setSettings(const PatternSettings&);
  virtual void update(unsigned long);
  virtual void draw(CLEDController& c, const Palette&) = 0;
protected:
  PatternSettings settings;  
  unsigned long time;

  void drawBar(float position, float width, CRGB color);
  void applyTailEffect();
};