/*
Author: Muhammad Hashir Bin Khalid
Date: 15th Dec 2022

This code reads LIN data from wire between motor controller and meter.

*/

#define BUTTON_PIN 12
byte val=B0;
//byte mybytes[12];
byte mybytes[12];

void setup()
{
  Serial.begin(9600);
  for (int i=0;i<12;i++){mybytes[i]=B0; }
 
  pinMode(BUTTON_PIN, INPUT);
}
int bits=0, byte_num=0;
int zero1=800, zero2=1100, one1=400, one2=600;
//int zero1=350, zero2=430, one1=180, one2=220;

void loop()
{
  unsigned long duration = pulseIn(BUTTON_PIN, LOW);
  if(duration>50000) {
    Serial.print(bits);
    for (int i=0;i<12;i++){Serial.print(","); Serial.print(mybytes[i],HEX); }
    Serial.print(",");
    Serial.println(duration);
    //Serial.print(val,HEX); 
  //Serial.print(",");  Serial.print(zeros); Serial.print(","); Serial.println(ones);
  val=0; byte_num=0; bits=0;}
  else if (duration<one2 and duration>one1) {
    //Serial.print("0"); 
    val <<= 1; val|=1; 
    bits++;}
  else if (duration<zero2 and duration>zero1) {
    //Serial.print("1");
    val <<= 1;  bits++;}
  else {
    Serial.print("Error:"); Serial.println(duration);}
  if(bits%8==0 and bits!=0){
    //Serial.print("Byte:");
    //Serial.println(val);
    mybytes[byte_num] = val; byte_num++;
    val = B0;
  }
}
