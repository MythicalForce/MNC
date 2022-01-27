#include "pattern.h"

void Pattern::update(CLEDController& c, unsigned long)
{
    //CRGB* leds = c.leds();
    int size = c.size();

    if ( millis() - settings.PatternUpdate >= settings.PatternDelay )
    {

        if ( settings.PatternWrapAround == YES && settings.PatternDirection == FORWARD )
        {
            settings.PatternPosition += 0.1f;

            //debug.info("[PATTERN]", "[INFO]", "Pattern Position %d", settings.PatternPosition);
            Serial.println(settings.PatternPosition);

            if ( settings.PatternActive == THEATHERCHASE )
            {
                if ( settings.PatternPosition >= 3 )
                    settings.PatternPosition = 0.0f;
            }
            else if ( settings.PatternActive == CYLON )
            {
                if ( settings.PatternPosition >= (size + settings.PatternBarLength) )
                    settings.PatternPosition = 0.0f;
            }
            else if ( settings.PatternActive == MITOSIS )
            {
                if ( settings.PatternPosition > size / 2 - 1 + settings.PatternBarLength )
                    settings.PatternPosition = 0.0f;
            }
            else
            {
                if ( settings.PatternPosition >= size )
                    settings.PatternPosition = 0.0f;
            }
        }
        else if ( settings.PatternWrapAround == YES && settings.PatternDirection == REVERSE )
        {
            settings.PatternPosition  -= 0.1f;

            if ( settings.PatternActive == THEATHERCHASE )
            {
                if ( settings.PatternPosition <= 0 )
                    settings.PatternPosition = 3;
            }
            else if ( settings.PatternActive == CYLON )
            {
                if ( settings.PatternPosition < 0 )
                    settings.PatternPosition = (size + settings.PatternBarLength );
            }
            else if ( settings.PatternActive == MITOSIS )
            {
                if ( settings.PatternPosition < 0 )
                    settings.PatternPosition = size / 2 - 1 + settings.PatternBarLength ;
            }
            else
            {
                if ( settings.PatternPosition <= 0 )
                    settings.PatternPosition = size;
            }
        }

        settings.PatternUpdate = millis();
    }
}