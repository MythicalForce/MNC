#include <Arduino.h>
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include "globals.h"
#include "secrets.h"
#include "network.h"
#include "debugger.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#include "devicelist.h"

#include "controller.h"

#include "pattern/solidcolor.h"

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
          // websocket::loop();
        }
    }
}

Solidcolor solidcolor;

void IRAM_ATTR DrawLoopTaskEntry(void *)
{
  for (;;)
  {
    TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed=1;
    TIMERG0.wdt_wprotect=0;

    solidcolor.draw(*strand1_cled);
    solidcolor.Pattern::update(*strand1_cled, 70);
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
  debug.info("[MAIN]", "[INFO]", "PSRAM : %u", ESP.getPsramSize());
  debug.info("[MAIN]", "[INFO]", "PSRAM Free : %u", ESP.getFreePsram());
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
    strand2_cled = &FastLED.addLeds<WS2812B, LED_PIN1, GRB>( _leds1, Config[DEVICE].NUMLED[1] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 2 ACTIVE on pin %d with %d/%d LEDs", LED_PIN2, Config[DEVICE].NUMLED[1], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 3
    strand3_cled = &FastLED.addLeds<WS2812B, LED_PIN1, GRB>( _leds2, Config[DEVICE].NUMLED[2] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 3 ACTIVE on pin %d with %d/%d LEDs", LED_PIN3, Config[DEVICE].NUMLED[2], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 4
    strand4_cled = &FastLED.addLeds<WS2812B, LED_PIN1, GRB>( _leds3, Config[DEVICE].NUMLED[3] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 4 ACTIVE on pin %d with %d/%d LEDs", LED_PIN4, Config[DEVICE].NUMLED[3], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 5
    strand5_cled = &FastLED.addLeds<WS2812B, LED_PIN1, GRB>( _leds4, Config[DEVICE].NUMLED[4] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 5 ACTIVE on pin %d with %d/%d LEDs", LED_PIN5, Config[DEVICE].NUMLED[4], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 6
    strand6_cled = &FastLED.addLeds<WS2812B, LED_PIN1, GRB>( _leds5, Config[DEVICE].NUMLED[5] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 6 ACTIVE on pin %d with %d/%d LEDs", LED_PIN6, Config[DEVICE].NUMLED[5], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 7
    strand7_cled = &FastLED.addLeds<WS2812B, LED_PIN1, GRB>( _leds6, Config[DEVICE].NUMLED[6] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 7 ACTIVE on pin %d with %d/%d LEDs", LED_PIN7, Config[DEVICE].NUMLED[6], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 8
    strand8_cled = &FastLED.addLeds<WS2812B, LED_PIN1, GRB>( _leds7, Config[DEVICE].NUMLED[7] ).setCorrection( TypicalLEDStrip );
    debug.info("[FASTLED]", "[SETUP]", "Strip 8 ACTIVE on pin %d with %d/%d LEDs", LED_PIN8, Config[DEVICE].NUMLED[7], LED_AMOUNT_PER_PIN);
  #endif
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

  //websocket::begin();
  debug.newline();

  xTaskCreatePinnedToCore(DrawLoopTaskEntry, "Draw Loop", STACK_SIZE, nullptr, DRAWING_PRIORITY, &g_taskDraw, DRAWING_CORE);
  //xTaskCreatePinnedToCore(NetworkHandlingLoopEntry, "Network Handling Loop", STACK_SIZE, nullptr, NET_PRIORITY, &g_taskNet, NET_CORE);
  xTaskCreatePinnedToCore(SocketServerTaskEntry, "Socket Server Loop", STACK_SIZE, nullptr, SOCKET_PRIORITY, &g_taskSocket, SOCKET_CORE);
}

void loop()
{
  // relay::loop();
}