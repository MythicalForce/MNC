#include "pattern.h"
/*
void Pattern::setSettings(const Settings& s)
{
    settings.pattern.PatternBrightness = s.pattern.PatternBrightness;
    settings.pattern.PatternActive     = s.pattern.PatternActive;
    settings.pattern.PatternDirection  = s.pattern.PatternDirection;
    settings.pattern.PatternDelay      = s.pattern.PatternDelay;
    settings.pattern.PatternTail       = s.pattern.PatternTail;
    settings.pattern.PatternFadeAmount = s.pattern.PatternFadeAmount;
    settings.pattern.PatternWrapAround = s.pattern.PatternWrapAround;
    settings.pattern.PatternBarLength  = s.pattern.PatternBarLength;
    settings.pattern.PatternColorUse   = s.pattern.PatternColorUse;

    Palette::setSettings(palSettings);
}

void Pattern::applyTailEffect(CRGB* leds, int size)
{
    switch (settings.pattern.PatternTail)
    {
        case DUST:
            for (int j = 0; j < size; j++)
            {
                if (random(10) == 1)
                {
                    leds[j].fadeToBlackBy(settings.pattern.PatternFadeAmount);
                }
            }
        break;
        case SOLID:
            fadeToBlackBy(leds, size, 255);
        break;
        
        default:
        break;
    }
}
*/