#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include "enum.h"

/*
class LEDSettings
{
public:
    // Update Settings
    unsigned long  PatternUpdate;
    unsigned long  PaletteUpdate;

    LEDSettings()
    {
        // Pattern Settings
        PatternBrightness      = 64;
        PatternActive          = CYLON;
        PatternDirection       = FORWARD;
        PatternDelay           = 127;
        PatternTail            = DUST;
        PatternFadeAmount      = 128;
        PatternWrapAround      = YES;
        PatternBarLength       = 4;

        // Palette Settings
        PaletteDelay           = 70;
        PaletteDirection       = FORWARD;
        PaletteMode            = ONECOLOR;
        PalettePicker          = 0;
        PaletteSelected        = palSUNSETREAL;
        PaletteBlend           = LINEARBLEND;

        // Update Settings
        PatternUpdate          = 0;
        PaletteUpdate          = 0;
    }

    // Functions
    bool TimeToUpdatePattern();
    bool TimeToUpdatePalette();
    void UpdateCurrentPalette();
    void update();
};
*/