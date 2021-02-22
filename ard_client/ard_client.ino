#define hwserial Serial1
// #define CMD_STRING

void setup() {
  Serial.begin(9600); // open serial to pc
  hwserial.begin(9600); // open serial to server uC
  pinMode(13, OUTPUT);
}

#ifdef CMD_STRING
  String cmd_uC; // serial command to execute from server uC
  
  void loop() {
    while(hwserial.available()>0) {
      // read serial from server uC
      cmd_uC = hwserial.readString();
      cmd_uC.trim(); // remove begin/end white spaces
      if(cmd_uC!=-1) {
        // if "on" turn on LED, tell pc LED on
        if(cmd_uC=="ON") {
          digitalWrite(13, HIGH);
          Serial.println("turned on LED");
        }
        // elif "off" turn off LED, tell pc LED off
        else if(cmd_uC=="OFF") {
          digitalWrite(13, LOW);
          Serial.println("turned off LED");
        }
        // elif "exit" send exit command to pc
        else if(cmd_uC=="EXIT") {
          Serial.println("exit");
        }
        // else do nothing, tell pc nothing done
        else {
          Serial.print("recieved cmd: |");
          Serial.print(cmd_uC);
          Serial.println("|");
        }
      }
    }
  }

#else
  int cmd_uC; // serial command to execute from server uC
  
  void loop() {
    while(hwserial.available()>0) {
      // read serial from server uC
      cmd_uC = hwserial.read();
      if(cmd_uC!=-1) {
        // if "on" turn on LED, tell pc LED on
        if(cmd_uC==49) { // should be 1
          digitalWrite(13, HIGH);
          Serial.println("turned on LED");
        }
        // elif "off" turn off LED, tell pc LED off
        else if(cmd_uC==48) { // should be 0
          digitalWrite(13, LOW);
          Serial.println("turned off LED");
        }
        // elif "exit" send exit command to pc
        else if(cmd_uC==50) { // should be 2
          Serial.println("exiting");
        }
        // else do nothing, tell pc nothing done
        else {
          Serial.print("recieved cmd: |");
          Serial.print(cmd_uC);
          Serial.println("|");
        }
      }
    }
  }
#endif
