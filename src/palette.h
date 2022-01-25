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
};

class Palette
{
public:
  void setSettings(const PaletteSettings&);

protected:
  PaletteSettings settings;  
  unsigned long time;
};