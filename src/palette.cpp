#include "palette.h"

CRGB Palette::PaletteMode(CLEDController& controller, int Index, int Brightness)
{
    CRGB* leds = controller.leds();
    int size = controller.size();

    switch ( settings.PaletteMode )
    {
        case          ONECOLOR: return ColorFromPalette(settings.PaletteCurrent, settings.PalettePicker, Brightness, settings.PaletteBlend); break;
        case       FULLPALETTE: return ColorFromPalette(settings.PaletteCurrent, Index * 255 / size, Brightness, settings.PaletteBlend); break;
        case FULLPALETTEMOVING: return ColorFromPalette(settings.PaletteCurrent, (settings.PalettePosition * 255 / size) - (Index * 255 / size), Brightness, settings.PaletteBlend); break;
    
        default: break;
    }

    return CRGB();
}