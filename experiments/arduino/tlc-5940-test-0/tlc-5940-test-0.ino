#include "Tlc5940.h"
#include <ArduinoJson.h>

const int TLC_CH = 16;

void setup() {
  Tlc.init();
  
  Serial.begin(57600);
  while (!Serial) {
    ;
  }
}

void loop() {
  Tlc.clear();
  
  if (Serial.available()) {
    char str[255];
    recvStr(str);

    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(str);
    JsonArray& memorys = root["memorys"];

    int ch = 0;
    int i = 0;
    int j = 0;
  
    for(JsonArray::iterator _sensors=memorys.begin(); _sensors!=memorys.end(); ++_sensors) {
      JsonArray& sensors = *_sensors;
  
      ch = i * TLC_CH;
      i++;
  
      for(JsonArray::iterator _memorys=sensors.begin(); _memorys!=sensors.end(); ++_memorys) {
        JsonArray& memory = *_memorys;
  
        ch += j * 4;
        j++;
  
        for(JsonArray::iterator _memory=memory.begin(); _memory!=memory.end(); ++_memory) {
          JsonObject& memory = *_memory;
  
          ch += 1;
  
//          Serial.println(ch);
//          Serial.println(atoi(memory["tempel"].as<const char*>()));

          Tlc.set(ch, atoi(memory["tempel"].as<const char*>()));
          Tlc.update();
        }
      }
    }

//    Serial.println(str);
    Serial.flush();
    
//    delay(1000);
  }
}

/**
 * establishContact
 */
void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("initialize");
    delay(300);
  }
}


void recvStr(char *buf) {
  int i = 0;
  char c;
  
  while (1) {
    if (Serial.available()) {
      c = Serial.read();
      buf[i] = c;
      if (c == '\n') break;
      i++;
    }
  }
  buf[i] = '\0';  // \0: end of string
}
