#define LIN_PIN 11
byte value=B0;
byte headerbytes[5] = {0x08,0x61,0x00,0x00,0x02};
byte hdatabytes[7] = {0x00,0x00,0x00,0x00,0x00,0x00,0x6B};
byte mybytes[12]={0x08,0x61,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x6A};
//byte mybytes[13]={0x04,0x30,0x80,0x30,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x05,0x00};
//byte mybytes2[13]={0x04,0x30,0x80,0x30,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00};
//8,61,0,0,3,0,0,0,0,0,0,6A
//0861003000000
//8,61,0,0,3,4,0,0,0,0,0,6E
//Speed: 8,61,0,0,43,0,0,0,53,0,0,79
//Speed: 8,61,0,0,43,0,0,0,84,0,0,AE
//Speed: 8,61,0,0,43,0,1,1,9C,0,0,B6
//{0x00,0x10,0xC2,0x00,0xC0,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
//97,4,30,80,30,1,80,0,0,0,0,0,5,0

void setup()
{
  Serial.begin(9600); 
  pinMode(LIN_PIN, OUTPUT);
  digitalWrite(LIN_PIN,LOW);
  Serial.println("LOW started");
  delay(5000);
  Serial.println("LOW ended");
  digitalWrite(LIN_PIN,HIGH);
  delay(740);
  digitalWrite(LIN_PIN,LOW);
  delayMicroseconds(100);
  value = 0x00;
for(int b=0; b<5;b++){
value = headerbytes[b];
for(int i = 0, mask = 0x80; i < 8; i++, mask = mask >> 1)
{ if(b==4 and i==7) break;
    if (value & mask) 
    {
      digitalWrite(LIN_PIN,LOW);
      delayMicroseconds(200);
      digitalWrite(LIN_PIN,HIGH);
      delayMicroseconds(400);
        // bit is on
    }
    else
    {
      digitalWrite(LIN_PIN,LOW);
      delayMicroseconds(400);
      digitalWrite(LIN_PIN,HIGH);
      delayMicroseconds(200);
        // bit is off
    }
}
}

digitalWrite(LIN_PIN, LOW);
delayMicroseconds(250);
digitalWrite(LIN_PIN,HIGH);
delayMicroseconds(250);


for(int b=0; b<7;b++){
value = hdatabytes[b];
for(int i = 0, mask = 0x80; i < 8; i++, mask = mask >> 1)
{
    if (value & mask) 
    {
      digitalWrite(LIN_PIN,LOW);
      delayMicroseconds(500);
      digitalWrite(LIN_PIN,HIGH);
      delayMicroseconds(1000);
        // bit is on
    }
    else
    {
      digitalWrite(LIN_PIN,LOW);
      delayMicroseconds(1000);
      digitalWrite(LIN_PIN,HIGH);
      delayMicroseconds(500);
        // bit is off
    }
}
}
}
int incomingByte=0;
void loop()
{
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    //String teststr = Serial.readString();  //read until timeout
    //teststr.trim();
    //int index = teststr.substring(0,2).toInt()

    mybytes[6]=0x00; mybytes[7]=0x00;
    if (incomingByte=='A'){mybytes[4]=0x03; mybytes[5]=0x04; mybytes[11]=0x6E; mybytes[8]=0x00;} //REVERSE
    else if (incomingByte=='B'){ mybytes[4]=0x03; mybytes[5]=0x00; mybytes[11]=0x6A; mybytes[8]=0x00;}
    else if (incomingByte=='C'){mybytes[4]=0x43; mybytes[11]=0x79; mybytes[8]=0x53;}
    else if (incomingByte=='D'){mybytes[4]=0x43; mybytes[11]=0xAE; mybytes[8]=0x84;}
    else if (incomingByte=='E'){mybytes[4]=0x43; mybytes[11]=0xB6; mybytes[8]=0x9C;}
    else if (incomingByte=='F'){mybytes[4]=0x43; mybytes[11]=0xAB; mybytes[8]=0x91;}
    else if (incomingByte=='G'){mybytes[7] = 0x03; mybytes[6]=0x03;}
    else if (incomingByte=='H'){mybytes[7] = 0x01; mybytes[6]=0x01;}
    else if (incomingByte=='I'){mybytes[7] = 0x02; mybytes[6]=0x02;}
    
//    else if (incomingByte=='E'){mybytes[4]=0x43; mybytes[7] = 0x01; mybytes[6]=0x01; mybytes[11]=0xB6; mybytes[8]=0x9C;}

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
digitalWrite(LIN_PIN,LOW);
delay(60);
digitalWrite(LIN_PIN,LOW);
delayMicroseconds(1000);
digitalWrite(LIN_PIN,HIGH);
delayMicroseconds(500);
for(int b=0; b<12;b++){
value = mybytes[b];
for(int i = 0, mask = 0x80; i < 8; i++, mask = mask >> 1)
{
    if (value & mask) 
    {
      digitalWrite(LIN_PIN,LOW);
      delayMicroseconds(500);
      digitalWrite(LIN_PIN,HIGH);
      delayMicroseconds(1000);
        // bit is on
    }
    else
    {
      digitalWrite(LIN_PIN,LOW);
      delayMicroseconds(1000);
      digitalWrite(LIN_PIN,HIGH);
      delayMicroseconds(500);
        // bit is off
    }
//if(b==12 and i==0) {digitalWrite(LIN_PIN,LOW); break;}
}
}
}
