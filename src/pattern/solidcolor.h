#pragma once

#include "pattern.h"
#include "draw.h"

class Solidcolor : public Pattern
{
public:
	virtual void draw(CLEDController& c)
	{
        CRGB* leds = c.leds();
        int size = c.size();
        fadeToBlackBy(leds, size, 255);

        for(float i = 0; i < size; i++)
        {   
            DrawPixels(c, i, 1, PaletteMode(c, i));
        }
    }
};