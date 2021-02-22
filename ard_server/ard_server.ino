#include<SoftwareSerial.h>
// #define CMD_STRING

SoftwareSerial client(10, 11);

String cmd_pc; // command to run from pc

void setup() {
  Serial.begin(9600); // open serial to pc
  client.begin(9600); // open serial to client uC
  pinMode(13, OUTPUT);
}

#ifdef CMD_STRING
  void loop() {
    cmd_pc = "";
    while(Serial.available()>0) { // read serial from pc
      cmd_pc = Serial.readStringUntil('/');
      // send command to client uC
      if(cmd_pc=="on") {
        // client.print(1, DEC);
        client.println("ON");
        Serial.println("on cmd sent");
      }
      else if(cmd_pc=="off") {
        // client.print(0, DEC);
        client.println("OFF");
        Serial.println("off cmd sent");
        }
      else if(cmd_pc=="exit") {
        // client.print(2, DEC);
        client.println("EXIT");
        Serial.println("exit cmd sent");
      }
      else{Serial.println("no cmd sent");}
    }
  }

#else
  void loop() {
    cmd_pc = "";
    while(Serial.available()>0) { // read serial from pc
      cmd_pc = Serial.readStringUntil('/');
      // send command to client uC
      if(cmd_pc=="on") {
        client.print(1, DEC);
        // client.println("ON");
        Serial.println("on cmd sent");
      }
      else if(cmd_pc=="off") {
        client.print(0, DEC);
        // client.println("OFF");
        Serial.println("off cmd sent");
        }
      else if(cmd_pc=="exit") {
        client.print(2, DEC);
        // client.println("EXIT");
        Serial.println("exit cmd sent");
      }
      else{Serial.println("no cmd sent");}
    }
  }
#endif
