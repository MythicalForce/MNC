#pragma once

#include "pattern.h"
#include "draw.h"

class TheaterChase : public Pattern
{
public:
	virtual void draw(CLEDController& c)
	{
        CRGB* leds = c.leds();
        int size = c.size();

        fadeToBlackBy(leds, size, 255);

        for (float i = settings.PatternPosition; i < size; i+= 3)
        {
            DrawPixels(c, i, 1, PaletteMode(c, i));
        }
    }

    virtual void update(CLEDController& c)
    {
        if ( millis() - settings.PatternUpdate >= settings.PatternDelay )
        {
            if ( settings.PatternWrapAround == YES && settings.PatternDirection == FORWARD )
            {
                settings.PatternPosition += 0.1f;

                if ( settings.PatternPosition >= 3 )
                    settings.PatternPosition = 0.0f;
            }
            else if ( settings.PatternWrapAround == YES && settings.PatternDirection == REVERSE )
            {
                settings.PatternPosition  -= 0.1f;

                if ( settings.PatternPosition <= 0 )
                    settings.PatternPosition = 3;
            }
            settings.PatternUpdate = millis();
        }
    }
};