#include <SPI.h>

#define CS    7
#define size  8192

int currentADDR = 0b000000000; // a8 >> a0
uint16_t DATA[512]; 
bool cont = true;
int addr = 0x0000;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV64); 
  pinMode(CS, OUTPUT);
  pinMode(5, INPUT);
  digitalWrite(CS,HIGH);

  delay (100);
}

void loop() {
  if(digitalRead(5) == true && cont){
    for(int i=0; i<512; i++){
     digitalWrite(CS,LOW);
     SPI.transfer16((0b1010100<<9) | currentADDR);  //
     DATA[i] = SPI.transfer16(0x0000);
     digitalWrite(CS,HIGH);
     currentADDR++;
    }
   //printarr();
   printdata();
   cont = false;
  }
}


void printdata(){
    Serial.print("0x0000 :     ");
    for (int j=0; j<512; j++){
    if((j+1)%8 != 0){
     Serial.print(DATA[j] >> 12, HEX);
     Serial.print((DATA[j] >> 8) & 0x0F, HEX);
     Serial.print(" ");
     Serial.print((DATA[j] >> 4) & 0x00F, HEX);
     Serial.print(DATA[j] & 0x000F, HEX);
     Serial.print(" ");
    }
    else{
    addr += 8;
    Serial.print(DATA[j] >> 12, HEX);
    Serial.print((DATA[j] >> 8) & 0x0F, HEX);
    Serial.print(" ");
    Serial.print((DATA[j] >> 4) & 0x00F, HEX);
    Serial.print(DATA[j] & 0x000F, HEX);
    Serial.println();
    if (j != 511){
    Serial.print("0x");
    Serial.print(addr >> 12, HEX);
    Serial.print((addr >> 8) & 0x0F, HEX);
    Serial.print((addr >> 4) & 0x00F, HEX);
    Serial.print(addr & 0x000F, HEX);
    Serial.print(" :     ");
    }
    }
    }
}

void printarr(){
  for (int j=0; j<512; j++){
    if((j+1)%8 != 0){
     Serial.print("0x");
     Serial.print(DATA[j] >> 12, HEX);
     Serial.print((DATA[j] >> 8) & 0x0F, HEX);
     Serial.print((DATA[j] >> 4) & 0x00F, HEX);
     Serial.print(DATA[j] & 0x000F, HEX);
     Serial.print(", ");
    }
  else{
    Serial.print("0x");
    Serial.print(DATA[j] >> 12, HEX);
    Serial.print((DATA[j] >> 8) & 0x0F, HEX);
    Serial.print((DATA[j] >> 4) & 0x00F, HEX);
    Serial.print(DATA[j] & 0x000F, HEX);
    if (j != 511)
     Serial.print(", ");
    Serial.println();
    }
  }
}