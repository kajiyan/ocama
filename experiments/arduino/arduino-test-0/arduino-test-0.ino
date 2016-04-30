void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
//  establishContact();
}

void loop() {
  Serial.println("TEST");
  
  char str[255];
  
  if (Serial.available()) {
    recvStr(str);
    Serial.println(str);
  }
  Serial.flush();
  
  delay(1000);
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
