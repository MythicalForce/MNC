#pragma once

#include <FastLED.h>
#include "settings.h"
#include "pattern.h"
#include "enum.h"

class LEDController
{
public:
  void updatePatternSettings(CLEDController& c, const Settings& s);
};