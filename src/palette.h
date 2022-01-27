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
    unsigned long  PalettePosition;
};

class Palette
{
public:
  void setSettings(const PaletteSettings&);
  CRGB PaletteMode(CLEDController& controller, int Index, int Brightness = 127 );

protected:
  PaletteSettings settings;
  unsigned long time;
};