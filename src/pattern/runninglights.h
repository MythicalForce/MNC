#pragma once

#include "pattern.h"
#include "draw.h"

class RunningLights : public Pattern
{
public:
	virtual void draw(CLEDController& c)
	{
        CRGB* leds = c.leds();
        int size = c.size();

        fadeToBlackBy(leds, size, 255);

        for (float i = 0; i < size; i++)
        {
            float a = 2 * (i + settings.PatternPosition) * 255 / (size - 1);
            float ni = (size - 1) - i;
            DrawPixels(c,ni, 1, PaletteMode(c, ni, sin8(a) * settings.PatternBrightness / 255));
        }
    }

    virtual void update(CLEDController& c)
    {
        int size = c.size();

        if ( millis() - settings.PatternUpdate >= settings.PatternDelay )
        {
            if ( settings.PatternWrapAround == YES && settings.PatternDirection == FORWARD )
            {
                settings.PatternPosition += 0.1f;

                if ( settings.PatternPosition >= size )
                    settings.PatternPosition = 0.0f;
            }
            else if ( settings.PatternWrapAround == YES && settings.PatternDirection == REVERSE )
            {
                settings.PatternPosition  -= 0.1f;

                if ( settings.PatternPosition <= 0 )
                    settings.PatternPosition = size;
            }
            settings.PatternUpdate = millis();
        }
    }
};