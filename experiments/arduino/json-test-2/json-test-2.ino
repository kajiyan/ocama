#include <ArduinoJson.h>


void setup() {
  Serial.begin(9600);
   while (!Serial) {
    // シリアルポートの初期化を待つ
    ;
  }

  StaticJsonBuffer<200> jsonBuffer;

  // char json[] = "{\"memorys\": [[48.756080,2.302038]]}";
  char json[] = "{\"memorys\": [[{\"tempel\": 36.5}, {\"tempel\": 37.5}]]}";
  
  JsonObject& root = jsonBuffer.parseObject(json);
  JsonArray& memorys = root["memorys"];

  for(JsonArray::iterator _memorys=memorys.begin(); _memorys!=memorys.end(); ++_memorys) {
    JsonArray& memory = *_memorys;

    for(JsonArray::iterator _memory=memory.begin(); _memory!=memory.end(); ++_memory) {
      JsonObject& memory = *_memory;

      Serial.println(memory["tempel"].as<const char*>());
    }
  }
}


void loop() {
  
}
