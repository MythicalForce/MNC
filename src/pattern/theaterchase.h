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

        for (float i = PatternPosition; i < size; i+= 3)
        {
            DrawPixels(c, i, 1, PaletteMode(c, i, PatternBrightness));
        }
    }

    virtual void update(CLEDController& c)
    {
        if ( millis() - PatternUpdate >= PatternDelay )
        {
            if ( PatternWrapAround == YES && PatternDirection == FORWARD )
            {
                PatternPosition += 0.1f;

                if ( PatternPosition >= 3 )
                    PatternPosition = 0.0f;
            }
            else if ( PatternWrapAround == YES && PatternDirection == REVERSE )
            {
                PatternPosition  -= 0.1f;

                if ( PatternPosition <= 0 )
                    PatternPosition = 3;
            }
            PatternUpdate = millis();
        }
    }
};