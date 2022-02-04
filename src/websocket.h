#pragma once

#include <globals.h>
#include <WebSocketsServer.h>
#include "enum.h"
#include "ArduinoJson.h"
#include "controller.h"

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
          //outData["stripnumled"] 
          outData["patternActive"]     = 1;
          outData["brightness"]        = 127;
          outData["patternDelay"]      = 70;
          //outData["patternSpacing"]
          outData["patternDirection"]  = 1;
          outData["patternTail"]       = 1;
          outData["patternFadeAmount"] = 70;
          outData["patternWrapAround"] = 0;
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