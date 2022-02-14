#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include "enum.h"
#include "settings.h"

class Pattern : public Settings
{
public:
  virtual void update(CLEDController& c) = 0;
  virtual void draw(CLEDController& c) = 0;
};