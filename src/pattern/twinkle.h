#pragma once

#include "pattern.h"
#include "draw.h"

class Twinkle : public Pattern
{
public:
	virtual void draw(CLEDController& c)
	{
        CRGB* leds = c.leds();
        int size = c.size();

        fadeToBlackBy(leds, size, PatternFadeAmount);
        int i = random8(0, size);
        DrawPixels(c, i, 1, PaletteMode(c, i, PatternBrightness));
    }

    virtual void update(CLEDController& c)
    {

    }
};