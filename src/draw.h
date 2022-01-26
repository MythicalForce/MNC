#include <Arduino.h>
#include <FastLED.h>
#include "enum.h"
#include "pattern.h"

CRGB ColorFraction(CRGB colorIn, float fraction);
void DrawPixels(float fPos, float count, CRGB color);
void TailMode();