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
            float a = 2 * (i + PatternPosition) * 255 / (size - 1);
            float ni = (size - 1) - i;
            DrawPixels(c,ni, 1, PaletteMode(c, ni, sin8(a) * PatternBrightness / 255));
        }
    }

    virtual void update(CLEDController& c)
    {
        int size = c.size();

        if ( millis() - PatternUpdate >= PatternDelay )
        {
            if ( PatternWrapAround == YES && PatternDirection == FORWARD )
            {
                PatternPosition += 0.1f;

                if ( PatternPosition >= size )
                    PatternPosition = 0.0f;
            }
            else if ( PatternWrapAround == YES && PatternDirection == REVERSE )
            {
                PatternPosition  -= 0.1f;

                if ( PatternPosition <= 0 )
                    PatternPosition = size;
            }
            PatternUpdate = millis();
        }
    }
};