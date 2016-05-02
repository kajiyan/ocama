String inputString = "";
boolean stringComplete = false;


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  inputString.reserve(200);
//  establishContact();
}

void loop() {
  Serial.println("TEST");

//  serialEvent(); //call the function
//  // print the string when a newline arrives:
//  if (stringComplete) {
//    stringComplete = false;
//    Serial.println(inputString);
//    // clear the string:
//    inputString = "";
//  }

  if (Serial.available()) {
    char str[255];
    recvStr(str);
    Serial.println(str);
    Serial.flush();
    delay(1000);
  }
  
  
//  char str[255];
//  
//  if (Serial.available()) {
//    recvStr(str);
//    Serial.println(str);
//  }
//  Serial.flush();
//  
//  delay(1000);
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



/**
 * serialEvent
 */
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
      Serial.flush();
    }
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
