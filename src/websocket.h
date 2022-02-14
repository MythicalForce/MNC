#pragma once

#include <globals.h>
#include <WebSocketsServer.h>
#include "enum.h"
#include "ArduinoJson.h"
#include "controller.h"

extern std::vector<Settings> settings;

WebSocketsServer webSocket = WebSocketsServer( 80 );

namespace websocket
{
  int selectedstrip;

  void webSocketEvent( uint8_t num, WStype_t type, uint8_t * payload, size_t length )
  {
    IPAddress ip = webSocket.remoteIP( num );

    StaticJsonDocument<256> inData;
    deserializeJson(inData, payload);

    DynamicJsonDocument outData(256);
    String outJsonData;

    DynamicJsonDocument infoData(256);
    String infoJsonData;

    switch (selectedstrip)
    {
    case 1: break;
    
    default:
      break;
    }

    switch ( type )
    {
      case WStype_CONNECTED:
        debug.success( "[SOCKET]", "[CLIENTCONNECT]", "[%u] from %d.%d.%d.%d url: %s", num, ip[0], ip[1], ip[2], ip[3], payload );
      break;

      case WStype_DISCONNECTED: 
        debug.info( "[SOCKET]", "[CLIENTDISCONNECT]", "[%u] Disconnected!", num );
      break;

      case WStype_ERROR:
        debug.error( "[SOCKET]", "[ERROR]", "Oh Shit!" );
        debug.error( "[SOCKET]", "[ERROR]", "[%u] Disconnected!", payload );
      break;

      case WStype_BIN:
      case WStype_TEXT:
        if ( inData.containsKey("reqDeviceInfo") )
        {
          Serial.println("Someone requested info!");
          outData["devicetype"]        = "ESP32";
          outData["devicename"]        = "Test Machine";
          outData["ledtype"]           = "STRIP";
          outData["stripnumled"]       = settings[selectedstrip].StripNumLed;
          outData["patternActive"]     = settings[selectedstrip].PatternActive;
          outData["brightness"]        = settings[selectedstrip].PatternBrightness;
          outData["patternDelay"]      = settings[selectedstrip].PatternDelay;
          outData["PatternBarLength"]  = settings[selectedstrip].PatternBarLength;
          outData["patternDirection"]  = settings[selectedstrip].PatternDirection;
          outData["patternTail"]       = settings[selectedstrip].PatternTail;
          outData["patternFadeAmount"] = settings[selectedstrip].PatternFadeAmount;
          outData["patternWrapAround"] = settings[selectedstrip].PatternWrapAround;
          outData["colorPicker"]       = 0;
          outData["paletteMode"]       = ONECOLOR;
          outData["selectedPalette"]   = palSUNSETREAL;
          outData["paletteBlendMode"]  = 1;

          serializeJson(outData, outJsonData);
          webSocket.sendTXT(num, outJsonData);
        }
        if ( inData.containsKey("DeviceSpecInfo") )
        {
          infoData["DSI"]                  = 1;
          infoData["dsi_SoftwareVersion"]  = FLASH_VERSION;
          infoData["dsi_TotalHeapSize"]    = ESP.getHeapSize();
          infoData["dsi_FreeHeapSize"]     = ESP.getFreeHeap();
          infoData["dsi_FreeSketchSpace"]  = ESP.getFreeSketchSpace();
          infoData["dsi_SketchSize"]       = ESP.getSketchSize();
          infoData["dsi_CpuFreqMhz"]       = ESP.getCpuFreqMHz();

          serializeJson(infoData, infoJsonData);
          Serial.println(infoJsonData);
          webSocket.sendTXT(0, infoJsonData);
        }
        if ( inData.containsKey("selectedstrip") )
        {
          selectedstrip = inData["selectedstrip"];
        }
        if ( inData.containsKey("brightness") )
        {
          settings[selectedstrip].PatternBrightness = inData["brightness"];
        }
        if ( inData.containsKey("patternActive") )
        {
          settings[selectedstrip].PatternActive = (E_Patterns)inData["patternActive"];
        }
        if ( inData.containsKey("patternDirection") )
        {
          settings[selectedstrip].PatternDirection = (E_Direction)inData["patternDirection"];
        }
        if ( inData.containsKey("patternDelay") )
        {
          settings[selectedstrip].PatternDelay = (int)inData["patternDelay"];
        }
        if ( inData.containsKey("PatternBarLength") )
        {
          settings[selectedstrip].PatternBarLength = inData["PatternBarLength"];
        }
        if ( inData.containsKey("patternTail") )
        {
          settings[selectedstrip].PatternTail = (E_Tail)inData["patternTail"];
        }
        if ( inData.containsKey("patternFadeAmount") )
        {
          settings[selectedstrip].PatternFadeAmount = (int)inData["patternFadeAmount"];
        }
        if ( inData.containsKey("patternWrapAround") )
        {
          settings[selectedstrip].PatternWrapAround = (E_WrapAround)inData["patternWrapAround"];
        }
        
        if ( inData.containsKey("paletteActive") )
        {
          settings[selectedstrip].PaletteSelected = (E_Palette)inData["paletteActive"];
        }
        if ( inData.containsKey("paletteSpeed") )
        {
          settings[selectedstrip].PaletteDelay = (int)inData["paletteSpeed"];
        }
        if ( inData.containsKey("paletteDirection") )
        {
          settings[selectedstrip].PaletteDirection = (E_Direction)inData["paletteDirection"];
        }
        if ( inData.containsKey("paletteMode") )
        {
          settings[selectedstrip].PaletteBlendMode = (E_PaletteMode)inData["paletteMode"];
        }
        if ( inData.containsKey("colorPicker") )
        {
          settings[selectedstrip].PalettePicker = (int)inData["colorPicker"];
        }
        if ( inData.containsKey("paletteBlendMode") )
        {
          settings[selectedstrip].PaletteBlend = (TBlendType)inData["paletteBlendMode"];
        }
      break;
      case WStype_FRAGMENT_TEXT_START:
      case WStype_FRAGMENT_BIN_START:
      case WStype_FRAGMENT:
      case WStype_FRAGMENT_FIN:
      case WStype_PING:
      case WStype_PONG:
      break;
    }
  }

  void begin()
  {    
    webSocket.begin();
    webSocket.onEvent( webSocketEvent );

    debug.success("[SOCKET]", "[STATUS]", "Websocket Online!");
  }

  void loop()
  {
    webSocket.loop();
  }
}