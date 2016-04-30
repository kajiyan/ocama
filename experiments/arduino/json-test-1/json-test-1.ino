#include <ArduinoJson.h>


void setup() {
  Serial.begin(9600);
   while (!Serial) {
    // シリアルポートの初期化を待つ
    ;
  }

  StaticJsonBuffer<200> jsonBuffer;

  char json[] = "{\"data\": [[48.756080,2.302038]]}";
  
  JsonObject& root = jsonBuffer.parseObject(json);
  JsonArray& dataArray = root["data"];

  for(JsonArray::iterator memorys=dataArray.begin(); memorys!=dataArray.end(); ++memorys) {
    JsonArray& values = *memorys;

    for(JsonArray::iterator it=values.begin(); it!=values.end(); ++it) {
      const char* value = *it;
      value = it->as<const char*>();
      Serial.println(value);
    } 
  }
}


void loop() {
  
}
