#include <ArduinoJson.h>


void setup() {
  Serial.begin(9600);
   while (!Serial) {
    // シリアルポートの初期化を待つ
    ;
  }

  StaticJsonBuffer<200> jsonBuffer;

  char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  
  JsonObject& root = jsonBuffer.parseObject(json);
  JsonArray& dataArray = root["data"];

  // 配列を取り回す
  for(JsonArray::iterator it=dataArray.begin(); it!=dataArray.end(); ++it) {
    // *it contains the JsonVariant which can be casted as usuals
    const char* value = *it;

    // this also works: 
    value = it->as<const char*>();
    Serial.println(value);
  }
  

  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

  const char* sensor = root["sensor"];
  long time = root["time"];
  double latitude = root["data"][0];
  double longitude = root["data"][1];

  Serial.println(sensor);
  Serial.println(time);
  Serial.println(latitude, 6);
  Serial.println(longitude, 6);
}


void loop() {
  
}
