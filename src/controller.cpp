#include "controller.h"

LEDController::LEDController(CLEDController& c) : _cled(c) { }

void LEDController::updatePatternSettings(const PatternSettings& s)
{
  /*
  switch (s.PatternActive)
  {
    case SOLIDCOLOR:  solidcolor(s);  break;

    default: break;
  }
  */
}