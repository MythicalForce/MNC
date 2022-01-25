#include "LEDController/pattern.h"

class Solidcolor : public Pattern
{
	virtual void Draw()
	{
        fadeToBlackBy(_Leds.data(), _NumLeds, 255);
    }
};