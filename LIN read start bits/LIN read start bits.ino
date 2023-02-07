/*
Author: Muhammad Hashir Bin Khalid
Date: 15th Dec 2022

This code reads LIN data from wire between motor controller and meter.

*/

#define BUTTON_PIN 12
byte val = B0;
//byte mybytes[12];
byte mybytes[5];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i <5; i++) { mybytes[i] = B0; }

  pinMode(BUTTON_PIN, INPUT);
}
int bits = 0, byte_num = 0;
//int zero1=800, zero2=1100, one1=400, one2=600;
int zero1 = 350, zero2 = 550, one1 = 170, one2 = 220;

void loop() {
  unsigned long duration = pulseIn(BUTTON_PIN, HIGH);
  //Serial.println(duration);
  //if(duration>800){Serial.print("Greater than 2000:"); Serial.println(duration); delay(1000);}
  if (duration > 600000) {
    bits++;
    val<<=1;
    //Serial.println("Start high received");
    while (bits <= 40) {
      duration = pulseIn(BUTTON_PIN, LOW);
      if(duration>one2 and duration<zero1) break;
      if ((duration < one2 and duration > one1) or (duration>700)) {
        //Serial.print("0");
        val <<= 1;
        val |= 1;
        bits++;
      } else if (duration < zero2 and duration > zero1) {
        //Serial.print("1");
        val <<= 1;
        bits++;
      } else {
        Serial.print("Error:");
        Serial.println(duration);
        Serial.print(":");
        Serial.println(bits);
        bits++;
      }
    if (bits % 8 == 0) {
      //Serial.print("Byte:");
      //Serial.println(val);
      mybytes[byte_num] = val;
      byte_num++;
      val = B0;
    }
    }

  Serial.print("Total bits received:");
  Serial.println(bits);
  for (int i = 0; i < 6; i++) {
    Serial.print(",");
    Serial.print(mybytes[i], HEX);
  }
  Serial.print("|");
  Serial.print(val);
  Serial.print(":");
  Serial.println(duration);
  //Serial.print(val,HEX);
  //Serial.print(",");  Serial.print(zeros); Serial.print(","); Serial.println(ones);
  val = 0;
  byte_num = 0;
  bits = 0;
  while(1) {Serial.println("in While 1"); delay(10000);}
  }
  }

