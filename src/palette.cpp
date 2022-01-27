#include "palette.h"
#include "palettelist.h"

CRGB Palette::PaletteMode(CLEDController& controller, int Index, int Brightness)
{
    //CRGB* leds = controller.leds();
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

void Palette::ChangePalette()
{
    switch ( settings.PaletteSelected )
    {
        case     palSUNSETREAL: settings.PaletteCurrent = Sunset_Real_gp;     break;
        case   palSUMMERSUNSET: settings.PaletteCurrent = SummerSunset_gp;    break;
        case        palRAINBOW: settings.PaletteCurrent = rainbow_gp;         break;
        case palCHRISTMASCANDY: settings.PaletteCurrent = christmas_candy_gp; break;
        case      palDARKSPACE: settings.PaletteCurrent = darkspace_gp;       break;
        case      palDEEPOCEAN: settings.PaletteCurrent = deepocean_gp;       break;
        case           palFIRE: settings.PaletteCurrent = fire_gp;            break;
        case         palBHW128: settings.PaletteCurrent = bhw1_28_gp;         break;
        case         palBHW119: settings.PaletteCurrent = bhw1_19_gp;         break;
        case         palBHW222: settings.PaletteCurrent = bhw2_22_gp;         break;
        case       palGREENMAN: settings.PaletteCurrent = bhw2_greenman_gp;   break;
        case         palBHW102: settings.PaletteCurrent = bhw1_02_gp;         break;
        case         palBHW113: settings.PaletteCurrent = bhw1_13_gp;         break;
        
        default: break;
    }
}