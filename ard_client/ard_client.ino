#define server Serial1

void setup() {
  Serial.begin(115200); // open serial to pc
  server.begin(9600); // open serial to server uC
  pinMode(13, OUTPUT);
  
  Serial.println("finished initialization");
  delay(1000);
  live_read_analog();
}

String cmd_uC; // serial command to execute from server uC

void loop() {
  while(server.available()>0) {
    // read serial from server uC
    cmd_uC = server.readStringUntil('/');
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
      else if(cmd_uC=="M") {
        Serial.print("recieved cmd: |");
        Serial.print(cmd_uC);
        Serial.println("|");
        parrot_reply();
      }
      else if(cmd_uC=="TEST") {
        Serial.print("recieved cmd: |");
        Serial.print(cmd_uC);
        Serial.println("|");
        live_read_analog();
      }
      // else do nothing, tell pc nothing done
      else {
        Serial.print("recieved cmd: |");
        Serial.print(cmd_uC);
        Serial.println("|");
        Serial.println("did nothing");
      }
    }
  }
}

void parrot_reply() {
  while(true) {
    if(server.available()) {
      cmd_uC = server.readStringUntil('/');
      cmd_uC.trim();
      if(cmd_uC=="S") {
        Serial.println("stop found");
        break;
       }
      Serial.println(cmd_uC);
    }
  }
}

void live_read_analog() {
  Serial.println("starting analog read");
  int volt;
  unsigned long nxt_time = millis();
  while(true) {
    if(server.available()) {
      cmd_uC = server.readStringUntil('/');
      cmd_uC.trim();
      Serial.println(cmd_uC);
      delay(500);
      if(cmd_uC=="S") {
        break;
      }
    }
    if(millis()>nxt_time) {
      nxt_time += 10;
      volt = analogRead(10);
      Serial.println(volt);
    }
  }
  Serial.println("stopped analog read");
}
