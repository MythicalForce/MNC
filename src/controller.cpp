#include "controller.h"

#include "pattern/solidcolor.h"
#include "pattern/theaterchase.h"
#include "pattern/runninglights.h"
#include "pattern/cylon.h"
#include "pattern/mitosis.h"
#include "pattern/juggle.h"
#include "pattern/twinkle.h"
#include "pattern/colorstacking.h"

Solidcolor solidcolor;
TheaterChase theaterchase;
Juggle juggle;
RunningLights runninglights;
Cylon cylon;
Mitosis mitosis;
Twinkle twinkle;
ColorStacking colorstacking;

Pattern *currentPattern[] = { &solidcolor, &theaterchase, &juggle, &runninglights, &cylon, &mitosis, &twinkle, &colorstacking };

LEDController::LEDController(CLEDController& c) : _cled(c) { }

void LEDController::updatePatternSettings(CLEDController& c, const Settings& s)
{
  currentPattern[s.PatternActive]->setSettings(s);
  currentPattern[s.PatternActive]->draw(c);
  currentPattern[s.PatternActive]->update(c);
  currentPattern[s.PatternActive]->ChangePalette();
}