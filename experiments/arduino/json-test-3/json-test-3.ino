#include <ArduinoJson.h>


const int TLC_CH = 16;


void setup() {
  Serial.begin(9600);
   while (!Serial) {
    // シリアルポートの初期化を待つ
    ;
  }

  // StaticJsonBuffer<200> jsonBuffer;
  DynamicJsonBuffer jsonBuffer;
  
  char json[] = "{\"memorys\": [[[{\"tempel\": 36.5}, {\"tempel\": 37.5}]]]}";

  JsonObject& root = jsonBuffer.parseObject(json);
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

        Serial.println(ch);
        Serial.println(memory["tempel"].as<const char*>());
      }
    }
  }
}


void loop() {
  
}
