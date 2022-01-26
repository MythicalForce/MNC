#include "controller.h"

LEDController::LEDController(CLEDController& c) : _cled(c) { }

void LEDController::updatePatternSettings(const PatternSettings& s)
{
  switch (s.PatternActive)
  {
    //case SOLIDCOLOR:  pattern = Solidcolor(s);  break;
    //case E_CYLON:   pattern = Cylon(s);   break;

    //default:        pattern = AllBlack(s);
  }
}