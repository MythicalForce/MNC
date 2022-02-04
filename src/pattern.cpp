#include "pattern.h"

void Pattern::applyTailEffect(CRGB* leds, int size)
{
    switch (settings.PatternTail)
    {
        case DUST:
            for (int j = 0; j < size; j++)
            {
                if (random(10) == 1)
                {
                    leds[j].fadeToBlackBy(settings.PatternFadeAmount);
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

PatternSettings Pattern::getSettings()
{
    return settings;
}