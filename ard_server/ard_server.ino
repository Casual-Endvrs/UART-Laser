#include<SoftwareSerial.h>
#include<Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include<Wire.h>

SoftwareSerial client(10, 11);

Adafruit_MPU6050 mpu;

String cmd_pc; // command to run from pc

void setup() {
  Serial.begin(115200); // open serial to pc
  Serial.setTimeout(100);
  client.begin(9600); // open serial to client uC
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("End of Setup");
}

void loop() {
  cmd_pc = "";
  while(Serial.available()>0) { // read serial from pc
    cmd_pc = Serial.readStringUntil('/');
    // send command to client uC
    if(cmd_pc=="on") {
      client.print("ON/");
      Serial.println("on cmd sent");
    }
    else if(cmd_pc=="off") {
      client.print("OFF/");
      Serial.println("off cmd sent");
      }
    else if(cmd_pc=="exit") {
      client.print("EXIT/");
      Serial.println("exit cmd sent");
    }
    else if(cmd_pc=="mpu") {
      Serial.println("initializing MPU data collection");
      client.print("M/");
      mpu_data();
      Serial.println("stopping MPU data collection");
    }
    else if(cmd_pc=="test") {
      Serial.println("initializing repeated analog read");
      client.print("TEST/");
      pulse_led();
    }
    else if(cmd_pc=="stop") {
      Serial.println("sending stop command");
      client.print("STOP/");
      pulse_led();
    }
    else{Serial.println("no cmd sent");}
  }
}

void mpu_data() {
  unsigned long nxt_time = millis();
  
  while(true) {
    if(millis()>nxt_time) {
      digitalWrite(13, HIGH);
      nxt_time += 333;
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      
      client.print( String(a.acceleration.x) );
      client.print( ';' );
      client.print( String(a.acceleration.y) );
      client.print( ';' );
      client.print( String(a.acceleration.z) );
      client.print( ';' );
      client.print( String(g.gyro.x) );
      client.print( ';' );
      client.print( String(g.gyro.y) );
      client.print( ';' );
      client.print( String(g.gyro.z) );
      client.print( ';' );
      client.print( String(temp.temperature) );
      client.print('/');
      digitalWrite(13, LOW);
    }
    if(Serial.available()) {
      cmd_pc = Serial.readString();
      cmd_pc.trim();
      if(cmd_pc=="stop") {
        client.print("S/");
        break;
      }
    }
  }
}

void pulse_led() {
  unsigned long nxt_tm = millis();
  bool pin_state = LOW;
  while(true) {
    if(Serial.available()) {
      cmd_pc = Serial.readString();
      cmd_pc.trim();
      if(cmd_pc=="stop") {break;}
    }
    if(millis()>nxt_tm) {
      pin_state = !pin_state;
      digitalWrite(12, pin_state);
      digitalWrite(13, pin_state);
      nxt_tm += 500;
    }
  }
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  client.print("S/");
  Serial.println("stop command sent");
}
