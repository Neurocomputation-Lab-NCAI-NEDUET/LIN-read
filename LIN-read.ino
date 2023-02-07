/*
Author: Muhammad Hashir Bin Khalid
Date: 25th Dec 2022

This code reads LIN data from wire between motor controller and meter.
It prints speed, gear, errors and alot more.
*/

#define BUTTON_PIN 12
byte val = B0;
byte temp;
bool debug = 1;
//byte mybytes[12];
byte mybytes[12];
int gear = 0, oldgear = 0;
int throttle = 0, oldth = 0;
int brake = 0, oldbr = 0;
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 12; i++) { mybytes[i] = B0; }

  pinMode(BUTTON_PIN, INPUT);
}
int bits = 0, byte_num = 0;
int zero1 = 800, zero2 = 1100, one1 = 370, one2 = 600;
//int zero1=350, zero2=430, one1=180, one2=220;
int firstbitrecvd = 0;
void loop() {
  unsigned long duration = pulseIn(BUTTON_PIN, HIGH, 50000);
  if (duration == 0) {
    if(bits==96){
    if (debug) {
      Serial.println();
      Serial.print(bits);
      for (int i = 0; i < 12; i++) {Serial.print(","); Serial.print(mybytes[i], HEX);}
    }
    //int speed = int(0.08*(mybytes[7]*255+mybytes[8])+0.39);    //For default motor on table
    int speed = int(0.17 * (mybytes[7] * 255 + mybytes[8]));  //For Gen1
    if (mybytes[5] & B00000100) {
      gear = 0;
    } else if (mybytes[4] & B10000000) {
      gear = 4;
    } else {
      gear = mybytes[4] & B00000011;
    }
    throttle = 0;
    brake = 0;
    if (mybytes[4] & B01000000) { throttle = 1; }
    if ((mybytes[4] & B00100000) and (mybytes[5] & B00000010)) { brake = 1; }
    if (oldth != throttle or oldbr != brake or oldgear != gear) {
      //Serial.println();
      Serial.print("Throttle=");
      Serial.print(throttle);
      Serial.print(",Brake=");
      Serial.print(brake);
      Serial.print(",Gear=");
      Serial.print(gear);
      oldth = throttle;
      oldbr = brake;
      oldgear = gear;
    }
    if (throttle == 1 or debug == 1) {
      //Serial.println();
      Serial.print(",Speed= ");
      Serial.print(speed);
    }}
    //Serial.println();
    //Serial.println(val);
    //Serial.print(val,HEX);
    //Serial.print(",");  Serial.print(zeros); Serial.print(","); Serial.println(ones);
    val = 0;
    byte_num = 0;
    bits = 0;
  } else if (duration < one2 and duration > one1) {
    //Serial.print("0");
    val <<= 1;  //val|=1;
    bits++;
  } else if (duration < zero2 and duration > zero1) {
    //Serial.print("1");
    val <<= 1;
    val |= 1;
    bits++;
  } else {
    Serial.print("Error:");
    Serial.println(duration);
  }
  if (bits % 8 == 0 and bits != 0) {
    //Serial.print("Byte:");
    //Serial.println(val);
    //Serial.print(bits); Serial.print("*"); Serial.print(byte_num); Serial.print("*"); Serial.print(firstbitrecvd); Serial.print("*");
    if (bits == 8 and (byte_num == 0 and firstbitrecvd == 0)) {  // Serial.print(temp); Serial.print("*");
      bits--;
      temp = val >> 7;
      firstbitrecvd = 1;
    } else {
      mybytes[byte_num] = val;
      byte_num++;
      val = B0;
      firstbitrecvd = 0;
    }
  }
}
