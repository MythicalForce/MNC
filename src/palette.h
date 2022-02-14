#pragma once

#include "settings.h"

struct PaletteSettings
{
    uint8_t        PaletteDelay;
    E_Direction    PaletteDirection;
    E_PaletteMode  PaletteMode;
    uint8_t        PalettePicker;
    E_Palette      PaletteSelected;
    CRGBPalette256 PaletteCurrent;
    TBlendType     PaletteBlend;
    float          PalettePosition;
    unsigned long  PaletteUpdate;

    PaletteSettings() : PaletteDelay(70), 
                        PaletteDirection(FORWARD), 
                        PaletteMode(ONECOLOR), 
                        PalettePicker(0), 
                        PaletteSelected(palSUNSETREAL), 
                        PaletteBlend(LINEARBLEND), 
                        PalettePosition(0)
    {

    }
};

class Palette : public Settings
{
public:
  void setSettings(const Settings& s);
  CRGB PaletteMode(CLEDController& controller, int Index, int Brightness = 127 );
  void ChangePalette();

protected:
  PaletteSettings settings;
  unsigned long time;
};