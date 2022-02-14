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

        const uint16_t TotalLength = size-1;

        static uint16_t end = TotalLength;
        static int block = size;
        static CRGB color = 0;

        // reset after each full sequence
        if ( block >= TotalLength / PatternBarLength )
        {
            block = 0;
            end = TotalLength;
            if ( PatternColorUse == RANDOM )
                color = CHSV( random( 0, 255 ), 255, 255 );
            PatternPosition = 0.0f;
        }
        if ( PatternColorUse == RANDOM )
            DrawPixels(c, PatternPosition, 1, color );
        else
            DrawPixels(c, PatternPosition, 1, PaletteMode( c, PatternPosition, PatternBrightness ) );

        if ( PatternPosition >= PatternBarLength )
        {
            leds[ (int)PatternPosition - PatternBarLength ].fadeToBlackBy( 255 );
        }

        if ( PatternPosition >= end )
        {
            PatternPosition = 0.0f;
            end -= PatternBarLength;
            if ( PatternColorUse == RANDOM )
                color = CHSV( random( 0, 255 ), 255, 255 );
            block++;
        }
    }

    virtual void update(CLEDController& c)
    {
        if ( millis() - PatternUpdate >= PatternDelay )
        {
            if ( PatternWrapAround == YES && PatternDirection == FORWARD )
            {
                PatternPosition += 0.1f;
            }
            else if ( PatternWrapAround == YES && PatternDirection == REVERSE )
            {
                PatternPosition  -= 0.1f;
            }
            PatternUpdate = millis();
        }
    }
};