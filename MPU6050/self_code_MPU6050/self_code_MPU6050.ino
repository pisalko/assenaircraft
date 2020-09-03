#include <Wire.h>

#define sAdr 0x68


void setup() {
  Serial.begin(9600);

  Wire.begin();
  Wire.setClock(400000);
  delay(2);

  //disabling temp sensor and putting sensor in continunos operating mode
  Wire.beginTransmission(sAdr);
  Wire.write(0x6B);
  Wire.write(0b00001000);
  Wire.endTransmission(true);

  // setting neshto si vij koe
  Wire.beginTransmission(sAdr);
  Wire.write(0x1B);
  Wire.endTransmission(true);
  Wire.requestFrom(sAdr, 1, true);
  char transit = Wire.read();
  transit |= _BV(4);
  Wire.beginTransmission(sAdr);
  Wire.write(0x1B);
  Wire.write(transit);
  Wire.endTransmission(true);

  //setting DLPF_CFG filter to sensitity 2 DA PITAM DALI TRQBVA DIGITAL LOW PASS FILTER
  Wire.beginTransmission(sAdr);
  Wire.write(0x1A);
  Wire.endTransmission(true);
  Wire.requestFrom(sAdr, 1, true);
  transit = Wire.read();
  Serial.println();
  Serial.println(transit, BIN);
  Serial.println();
  transit |= _BV(0);
  Wire.beginTransmission(sAdr);
  Wire.write(0x1A);
  Wire.write(transit);
  Wire.endTransmission(true);

  //proverka
  Wire.beginTransmission(sAdr);
  Wire.write(0x1A);
  Wire.endTransmission(false);
  
  Wire.requestFrom(sAdr, 1, true);

  delay(50);
  while (Wire.available())
  {
    int vale = Wire.read();
    //Serial.println(vale, BIN);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  Wire.beginTransmission(sAdr);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(sAdr, 6, true);



  delay(2000);
}
