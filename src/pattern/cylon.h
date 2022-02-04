#pragma once

#include "pattern.h"
#include "draw.h"

class Cylon : public Pattern
{
public:
	virtual void draw(CLEDController& c)
	{
        CRGB* leds = c.leds();
        int size = c.size();

        for ( float i = 0; i < settings.PatternBarLength; i++ )
        {  
            float pi = settings.PatternPosition + i;
            DrawPixels(c, pi, 1, PaletteMode(c, pi ) );
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

                if ( settings.PatternPosition >= size )
                    settings.PatternPosition = 0.0f;
            }
            else if ( settings.PatternWrapAround == YES && settings.PatternDirection == REVERSE )
            {
                settings.PatternPosition  -= 0.1f;

                if ( settings.PatternPosition < 0 )
                    settings.PatternPosition = size;
            }
            settings.PatternUpdate = millis();
        }
    }
};