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

        for ( float i = 0; i < settings.PatternBarLength; i++ )
        {  
            float pi = settings.PatternPosition + i;
            float ni = ( size - 1 ) - pi;
            DrawPixels(c, pi, 1, PaletteMode(c, pi ) );
            DrawPixels(c, ni, 1, PaletteMode( c, ni ) );
        }
        applyTailEffect(leds, size);
    }

    virtual void update(CLEDController& c)
    {
        int size = c.size();

        if ( millis() - settings.PatternUpdate >= settings.PatternDelay )
        {
            if ( settings.PatternWrapAround == YES && settings.PatternDirection == FORWARD )
            {
                settings.PatternPosition += 0.1f;

                if ( settings.PatternPosition > size / 2)
                    settings.PatternPosition = 0.0f;
            }
            else if ( settings.PatternWrapAround == YES && settings.PatternDirection == REVERSE )
            {
                settings.PatternPosition  -= 0.1f;

                if ( settings.PatternPosition < 0 )
                    settings.PatternPosition = size / 2;
            }
            settings.PatternUpdate = millis();
        }
    }
};