#pragma once

#include "pattern.h"
#include "draw.h"

class Juggle : public Pattern
{
public:
	virtual void draw(CLEDController& c)
	{
        CRGB* leds = c.leds();
        int size = c.size();

        int dothue = 0;
        int balls = 8;

        for (float i = 0; i < balls; i++)
        {
            DrawPixels(c, beatsin16(i + 7, 0, size - 1), 1, CHSV(dothue, 255, PatternBrightness));
            dothue += 32;
        }
        applyTailEffect(leds, size);
    }

    virtual void update(CLEDController& c)
    {

    }
};