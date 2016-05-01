#include "Tlc5940.h"


void setup() {
  Tlc.init();
  
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
}

void loop() {
  Tlc.clear();
  Tlc.set(0, 100);
  Tlc.update();
  
  if (Serial.available()) {
    char str[255];
    recvStr(str);

    
    
    Serial.println(str);
    Serial.flush();
    delay(1000);
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
