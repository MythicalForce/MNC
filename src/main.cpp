#include <Arduino.h>
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include "globals.h"
#include "secrets.h"
#include "network.h"
#include "debugger.h"
#include "websocket.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "devicelist.h"

#include "pattern/solidcolor.h"
#include "pattern/theaterchase.h"
#include "pattern/runninglights.h"
#include "pattern/cylon.h"
#include "pattern/mitosis.h"
#include "pattern/juggle.h"
#include "pattern/twinkle.h"
#include "pattern/colorstacking.h"

//
// Task Handles to our running threads
//

TaskHandle_t g_taskDraw   = nullptr;
TaskHandle_t g_taskRelay  = nullptr;
TaskHandle_t g_taskNet    = nullptr;
TaskHandle_t g_taskSocket = nullptr;

#if NUM_CHANNELS >= 1
  CRGB _leds0[Config[DEVICE].NUMLED[0]];
  CLEDController *strand1_cled;
  LEDController strand1(*strand1_cled);
#endif

#if NUM_CHANNELS >= 2
  CRGB _leds1[Config[DEVICE].NUMLED[1]];
  CLEDController *strand2_cled;
  LEDController strand2(*strand2_cled);
#endif

#if NUM_CHANNELS >= 3
  CRGB _leds2[Config[DEVICE].NUMLED[2]];
  CLEDController *strand3_cled;
  LEDController strand3(*strand3_cled);
#endif

#if NUM_CHANNELS >= 4
  CRGB _leds3[Config[DEVICE].NUMLED[3]];
  CLEDController *strand4_cled;
  LEDController strand4(*strand4_cled);
#endif

#if NUM_CHANNELS >= 5
  CRGB _leds4[Config[DEVICE].NUMLED[4]];
  CLEDController *strand5_cled;
  LEDController strand5(*strand5_cled);
#endif

#if NUM_CHANNELS >= 6
  CRGB _leds5[Config[DEVICE].NUMLED[5]];
  CLEDController *strand6_cled;
  LEDController strand6(*strand6_cled);
#endif

#if NUM_CHANNELS >= 7
  CRGB _leds6[Config[DEVICE].NUMLED[6]];
  CLEDController *strand7_cled;
  LEDController strand7(*strand7_cled);
#endif

#if NUM_CHANNELS >= 8
  CRGB _leds7[Config[DEVICE].NUMLED[7]];
  CLEDController *strand8_cled;
  LEDController strand8(*strand8_cled);
#endif

void IRAM_ATTR SocketServerTaskEntry(void *)
{
    for (;;)
    {
        if (WiFi.isConnected())
        {
          websocket::loop();
        }
    }
}

Solidcolor solidcolor;
TheaterChase theaterchase;
RunningLights runninglights;
Cylon cylon;
Mitosis mitosis;
Juggle juggle;
Twinkle twinkle;
ColorStacking colorstacking;

void IRAM_ATTR DrawLoopTaskEntry(void *)
{
  for (;;)
  {
    TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed=1;
    TIMERG0.wdt_wprotect=0;

    //solidcolor.draw(*strand8_cled);
    //solidcolor.Palette::ChangePalette();

    //theaterchase.draw(*strand8_cled);
    //theaterchase.update(*strand8_cled);
    //theaterchase.Palette::ChangePalette();

    //runninglights.draw(*strand8_cled);
    //runninglights.update(*strand8_cled);
    //runninglights.Palette::ChangePalette();

    //cylon.draw(*strand8_cled);
    //cylon.update(*strand8_cled);
    //cylon.Palette::ChangePalette();

    //mitosis.draw(*strand8_cled);
    //mitosis.update(*strand8_cled);
    //mitosis.Palette::ChangePalette();

    //juggle.draw(*strand8_cled);

    //twinkle.draw(*strand8_cled);
    //twinkle.Palette::ChangePalette();

    colorstacking.draw(*strand8_cled);
    colorstacking.update(*strand8_cled);
    colorstacking.Palette::ChangePalette();

    /*
    strand1.updatePatternSettings();
    strand2.updatePatternSettings();
    strand3.updatePatternSettings();
    strand4.updatePatternSettings();
    strand5.updatePatternSettings();
    strand6.updatePatternSettings();
    strand7.updatePatternSettings();
    strand8.updatePatternSettings();
    */

    strand1_cled->show(_leds0, strand1_cled->size(), 255);
    strand2_cled->show(_leds1, strand2_cled->size(), 255);
    strand3_cled->show(_leds2, strand3_cled->size(), 255);
    strand4_cled->show(_leds3, strand4_cled->size(), 255);
    strand5_cled->show(_leds4, strand5_cled->size(), 255);
    strand6_cled->show(_leds5, strand6_cled->size(), 255);
    strand7_cled->show(_leds6, strand7_cled->size(), 255);
    strand8_cled->show(_leds7, strand8_cled->size(), 255);
  }
}

void setup()
{
  Serial.begin(115200);

  debug.clearMonitor();

  debug.text("------------------------------------------------------------------------------------- \n");
  debug.text("- Mythical Neon Controller                                                  Startup - \n");
  debug.text("------------------------------------------------------------------------------------- \n");

  debug.info("[MAIN]", "[INFO]", "Software Version : %u", FLASH_VERSION);
  debug.info("[MAIN]", "[INFO]", "ESP32 Free Memory : %u", ESP.getFreeHeap());
  debug.info("[MAIN]", "[INFO]", "ESP32 Clock Freq : %d MHz", ESP.getCpuFreqMHz());
  debug.success("[MAIN]", "[INFO]", "Startup complete!");
  debug.newline();

  debug.text("------------------------------------------------------------------------------------- \n");
  debug.text("- FASTLED                                                                   Startup - \n");
  debug.text("------------------------------------------------------------------------------------- \n");
  #if NUM_CHANNELS >= 1
    strand1_cled = &FastLED.addLeds<WS2812B, LED_PIN1, GRB>( _leds0, Config[DEVICE].NUMLED[0] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 1 ACTIVE on pin %d with %d/%d LEDs", LED_PIN1, Config[DEVICE].NUMLED[0], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 2
    strand2_cled = &FastLED.addLeds<WS2812B, LED_PIN2, GRB>( _leds1, Config[DEVICE].NUMLED[1] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 2 ACTIVE on pin %d with %d/%d LEDs", LED_PIN2, Config[DEVICE].NUMLED[1], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 3
    strand3_cled = &FastLED.addLeds<WS2812B, LED_PIN3, GRB>( _leds2, Config[DEVICE].NUMLED[2] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 3 ACTIVE on pin %d with %d/%d LEDs", LED_PIN3, Config[DEVICE].NUMLED[2], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 4
    strand4_cled = &FastLED.addLeds<WS2812B, LED_PIN4, GRB>( _leds3, Config[DEVICE].NUMLED[3] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 4 ACTIVE on pin %d with %d/%d LEDs", LED_PIN4, Config[DEVICE].NUMLED[3], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 5
    strand5_cled = &FastLED.addLeds<WS2812B, LED_PIN5, GRB>( _leds4, Config[DEVICE].NUMLED[4] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 5 ACTIVE on pin %d with %d/%d LEDs", LED_PIN5, Config[DEVICE].NUMLED[4], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 6
    strand6_cled = &FastLED.addLeds<WS2812B, LED_PIN6, GRB>( _leds5, Config[DEVICE].NUMLED[5] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 6 ACTIVE on pin %d with %d/%d LEDs", LED_PIN6, Config[DEVICE].NUMLED[5], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 7
    strand7_cled = &FastLED.addLeds<WS2812B, LED_PIN7, GRB>( _leds6, Config[DEVICE].NUMLED[6] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 7 ACTIVE on pin %d with %d/%d LEDs", LED_PIN7, Config[DEVICE].NUMLED[6], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 8
    strand8_cled = &FastLED.addLeds<WS2812B, LED_PIN8, GRB>( _leds7, Config[DEVICE].NUMLED[7] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 8 ACTIVE on pin %d with %d/%d LEDs", LED_PIN8, Config[DEVICE].NUMLED[7], LED_AMOUNT_PER_PIN);
  #endif

  FastLED.setBrightness(127);

  debug.newline();

  debug.text("------------------------------------------------------------------------------------- \n");
  debug.text("- RELAY                                                                     Startup - \n");
  debug.text("------------------------------------------------------------------------------------- \n");
  //relay::begin();
  debug.newline();

  debug.text("------------------------------------------------------------------------------------- \n");
  debug.text("- NETWORK                                                                   Startup - \n");
  debug.text("------------------------------------------------------------------------------------- \n");
  network::wifi::begin();
  network::ble::begin();
  debug.newline();

  debug.text("------------------------------------------------------------------------------------- \n");
  debug.text("- Websocket                                                                 Startup - \n");
  debug.text("------------------------------------------------------------------------------------- \n");
  websocket::begin();
  debug.newline();

  xTaskCreatePinnedToCore(DrawLoopTaskEntry, "Draw Loop", STACK_SIZE, nullptr, DRAWING_PRIORITY, &g_taskDraw, DRAWING_CORE);
  //xTaskCreatePinnedToCore(NetworkHandlingLoopEntry, "Network Handling Loop", STACK_SIZE, nullptr, NET_PRIORITY, &g_taskNet, NET_CORE);
  xTaskCreatePinnedToCore(SocketServerTaskEntry, "Socket Server Loop", STACK_SIZE, nullptr, SOCKET_PRIORITY, &g_taskSocket, SOCKET_CORE);
}

  void vTaskGetRunTimeStats(char *buffer)
  {
    
  }

void loop()
{
  // relay::loop();
}