#include "draw.h"

CRGB ColorFraction(CRGB colorIn, float fraction)
{
   fraction = min(1.0f, fraction);
   return CRGB(colorIn).fadeToBlackBy(255 * (1.0f - fraction));
}

void DrawPixels(CLEDController& controller, float fPos, float count, CRGB color)
{
    CRGB* leds = controller.leds();
    int size = controller.size();

    float availFirstPixel = 1.0f - (fPos - (long)(fPos));
    float amtFirstPixel = min(availFirstPixel, count);
    float remaining = min(count, size-fPos);
    int iPos = fPos;

    if (remaining > 0.0f)
    {
        CRGB c = ColorFraction(color, amtFirstPixel);
        CRGB& p = leds[iPos++];
        p.r = max(p.r, c.r);
        p.g = max(p.g, c.g);
        p.b = max(p.b, c.b);
        remaining -= amtFirstPixel;
    }

   // Now draw any full pixels in the middle

    while (remaining > 1.0f)
    {
        leds[iPos++] += color;
        remaining--;
    }

   // Draw tail pixel, up to a single full pixel

    if (remaining > 0.0f)
    {
        CRGB c = ColorFraction(color, remaining);
        CRGB& p = leds[iPos];
        p.r = max(p.r, c.r);
        p.g = max(p.g, c.g);
        p.b = max(p.b, c.b);
    }
}
