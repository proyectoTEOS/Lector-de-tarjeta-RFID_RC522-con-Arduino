/*
  Created by TEOS
  Domotic with Arduino https://goo.gl/btZpjs
  YouTube https://goo.gl/k7TUSZ
  Instagram https://goo.gl/zEIjia
  Facebook https://goo.gl/eivraR
  Twitter https://goo.gl/du5Wgn
  Github https://goo.gl/Xl5IiS
  WEB https://www.proyecto-teos.com
*/

#include <SPI.h>
#include <MFRC522.h> //https://github.com/miguelbalboa/rfid

MFRC522 mrfInstanceT(10, 9);
uint8_t myTagIDT[4] = {0xCA, 0x04, 0x1F, 0xCE};
String resultSerialT;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mrfInstanceT.PCD_Init();
  resultSerialT = "Coloque el TAG en el lector de tarjeta.";
  Serial.println(resultSerialT);
}

void loop() {
  if (mrfInstanceT.PICC_IsNewCardPresent()) {
    if (mrfInstanceT.PICC_ReadCardSerial()) {
      resultSerialT = (comparisonTagT(mrfInstanceT.uid.uidByte, myTagIDT, 4)) ? "TAG conocido" : "TAG desconocido";
      Serial.println(resultSerialT);
      mrfInstanceT.PICC_HaltA();
    }
  }
  delay(500);
}

bool comparisonTagT(uint8_t* incomingTagT, uint8_t* currentTagT, uint8_t length) {
  for (uint8_t indexT = 0; indexT < length; indexT++) {
    if (incomingTagT[indexT] != currentTagT[indexT])
      return false;
  }
  return true;
}
