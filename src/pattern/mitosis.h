#pragma once

#include "pattern.h"
#include "draw.h"

class Mitosis : public Pattern
{
public:
	virtual void draw(CLEDController& c)
	{
        CRGB* leds = c.leds();
        int size = c.size();

        for ( float i = 0; i < PatternBarLength; i++ )
        {  
            float pi = PatternPosition + i;
            float ni = ( size - 1 ) - pi;
            DrawPixels(c, pi, 1, PaletteMode( c, pi, PatternBrightness ) );
            DrawPixels(c, ni, 1, PaletteMode( c, ni, PatternBrightness ) );
        }
        applyTailEffect(leds, size);
    }

    virtual void update(CLEDController& c)
    {
        int size = c.size();

        if ( millis() - PatternUpdate >= PatternDelay )
        {
            if ( PatternWrapAround == YES && PatternDirection == FORWARD )
            {
                PatternPosition += 0.1f;

                if ( PatternPosition > size / 2)
                    PatternPosition = 0.0f;
            }
            else if ( PatternWrapAround == YES && PatternDirection == REVERSE )
            {
                PatternPosition  -= 0.1f;

                if ( PatternPosition < 0 )
                    PatternPosition = size / 2;
            }
            PatternUpdate = millis();
        }
    }
};