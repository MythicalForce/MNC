#include "settings.h"
#include "palettelist.h"
#include <FastLED.h>
#include "enum.h"

void Settings::setSettings(const Settings& s)
{
    PatternBrightness = s.PatternBrightness;
    PatternActive     = s.PatternActive;
    PatternDirection  = s.PatternDirection;
    PatternDelay      = s.PatternDelay;
    PatternTail       = s.PatternTail;
    PatternFadeAmount = s.PatternFadeAmount;
    PatternWrapAround = s.PatternWrapAround;
    PatternBarLength  = s.PatternBarLength;
    PatternColorUse   = s.PatternColorUse;

    PaletteDelay      = s.PaletteDelay;
    PaletteDirection  = s.PaletteDirection;
    PaletteBlendMode  = s.PaletteBlendMode;
    PalettePicker     = s.PalettePicker;
    PaletteSelected   = s.PaletteSelected;
    PaletteBlend      = s.PaletteBlend;
}

void Settings::applyTailEffect(CRGB* leds, int size)
{
    switch (PatternTail)
    {
        case DUST:
            for (int j = 0; j < size; j++)
            {
                if (random(10) == 1)
                {
                    leds[j].fadeToBlackBy(PatternFadeAmount);
                }
            }
        break;
        case SOLID:
            fadeToBlackBy(leds, size, PatternFadeAmount);
        break;
        
        default:
        break;
    }
}

CRGB Settings::PaletteMode(CLEDController& controller, int Index, int Brightness)
{
    //CRGB* leds = controller.leds();
    int size = controller.size();

    switch ( PaletteBlendMode )
    {
        case          ONECOLOR: return ColorFromPalette(PaletteCurrent, PalettePicker, Brightness, PaletteBlend); break;
        case       FULLPALETTE: return ColorFromPalette(PaletteCurrent, Index * 255 / size, Brightness, PaletteBlend); break;
        case FULLPALETTEMOVING: return ColorFromPalette(PaletteCurrent, (PalettePosition * 255 / size) - (Index * 255 / size), Brightness, PaletteBlend); break;
    
        default: break;
    }

    return CRGB();
}

void Settings::ChangePalette()
{
    switch ( PaletteSelected )
    {
        case     palSUNSETREAL: PaletteCurrent = Sunset_Real_gp;     break;
        case   palSUMMERSUNSET: PaletteCurrent = SummerSunset_gp;    break;
        case        palRAINBOW: PaletteCurrent = rainbow_gp;         break;
        case palCHRISTMASCANDY: PaletteCurrent = christmas_candy_gp; break;
        case      palDARKSPACE: PaletteCurrent = darkspace_gp;       break;
        case      palDEEPOCEAN: PaletteCurrent = deepocean_gp;       break;
        case           palFIRE: PaletteCurrent = fire_gp;            break;
        case         palBHW128: PaletteCurrent = bhw1_28_gp;         break;
        case         palBHW119: PaletteCurrent = bhw1_19_gp;         break;
        case         palBHW222: PaletteCurrent = bhw2_22_gp;         break;
        case       palGREENMAN: PaletteCurrent = bhw2_greenman_gp;   break;
        case         palBHW102: PaletteCurrent = bhw1_02_gp;         break;
        case         palBHW113: PaletteCurrent = bhw1_13_gp;         break;
        
        default: break;
    }
}