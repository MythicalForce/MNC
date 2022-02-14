#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include "enum.h"

class Settings
{
public:
    uint8_t        StripNumLed;
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

    uint8_t        PaletteDelay;
    E_Direction    PaletteDirection;
    E_PaletteMode  PaletteBlendMode;
    uint8_t        PalettePicker;
    E_Palette      PaletteSelected;
    CRGBPalette256 PaletteCurrent;
    TBlendType     PaletteBlend;
    float          PalettePosition;
    unsigned long  PaletteUpdate;

    Settings()
    {
        PatternBrightness = 64;
        PatternActive     = CYLON;
        PatternDirection  = FORWARD;
        PatternDelay      = 70;
        PatternTail       = DUST;
        PatternFadeAmount = 128;
        PatternWrapAround = YES;
        PatternBarLength  = 4;
        PatternColorUse   = RANDOM;
        PatternPosition   = 0.0f;

        PaletteDelay      = 70;
        PaletteDirection  = FORWARD;
        PaletteBlendMode  = ONECOLOR;
        PalettePicker     = 0;
        PaletteSelected   = palSUNSETREAL;
        PaletteBlend      = LINEARBLEND;
        PalettePosition   = 0;
    }

    void setSettings(const Settings& s);
    void applyTailEffect(CRGB* leds, int size);
    CRGB PaletteMode(CLEDController& controller, int Index, int Brightness = 127 );
    void ChangePalette();
};