#pragma once

#include <FastLED.h>
#include "settings.h"
#include "pattern.h"

class LEDController
{
public:
  LEDController(CLEDController& c);
  void updatePatternSettings(const PatternSettings& s);

private:
  CLEDController& _cled;
};