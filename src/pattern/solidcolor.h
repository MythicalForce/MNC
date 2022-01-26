#include "pattern.h"
#include "draw.h"

class Solidcolor : public Pattern
{
	virtual void draw(CLEDController& c, const Palette&)
	{
        CRGB* leds = c.leds();
        int size = c.size();
        fadeToBlackBy(leds, size, 255);

        for(float i = 0; i < size; i++)
        {   
            DrawPixels(i, 1, PaletteMode(c, i));
        }
    }

	virtual void update()
	{
        
    }
};