#pragma once

#include "pattern.h"
#include "draw.h"

class ColorStacking : public Pattern
{
public:
	virtual void draw(CLEDController& c)
	{
        CRGB* leds = c.leds();
        int size = c.size();

        const uint16_t TotalLength = size;

        static uint16_t end = TotalLength;
        static int block = 0;
        static CRGB color = 0;
        static int i = 0;  

        // reset after each full sequence
        if ( block >= TotalLength / settings.PatternBarLength )
        {
            block = 0;
            end = TotalLength;
            if ( settings.PatternColorUse == RANDOM )
                color = CHSV( random( 0, 255 ), 255, 255 );
            i = 0;
        }

        if ( settings.PatternColorUse == RANDOM )
            leds[ i ] = color;
        else
            leds[ i ] = PaletteMode(c, i );

        if ( i >= settings.PatternBarLength )
        {
            leds[ i - settings.PatternBarLength ].fadeToBlackBy( 255 );
        }

        if ( ++i >= end )
        {
            i = 0;
            end -= settings.PatternBarLength;
            if ( settings.PatternColorUse == RANDOM )
                color = CHSV( random( 0, 255 ), 255, 255 );
            block++;
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