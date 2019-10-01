# Lector de tarjeta RFID RC522 con Arduino
En esta ocasión trabajaremos con el lector de tarjetas RFID MIFARE RC522 utilizando Arduino.

### Requisitos
- Tener el IDE de [Arduino](https://www.arduino.cc/en/Main/Software) (o el de tu preferencia) con la versión más actual
- Contar con las librería [MFRC522](https://github.com/miguelbalboa/rfid)
- Tener el material para hacer el proyecto

### Código
**[Aqui](https://github.com/proyectoTEOS/Lector-de-tarjeta-RFID_RC522-con-Arduino/blob/master/Lector-de-tarjeta-RFID_RC522-con-Arduino.ino)** podrás obtener el link del código, también dejaremos
una vista previa aquí abajo.

```c++
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
uint8_t myTagIDT[4] = {0xCA, 0x04, 0x1F, 0xCE}; //Place your ID here
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
```

### Diagrama
El siguiente esquemático muestra como se debe conectar todos los componentes con la placa.
![](https://github.com/proyectoTEOS/Lector-de-tarjeta-RFID_RC522-con-Arduino/blob/master/lector-de-tarjeta-rfid_rc522-con-arduino-5.jpg)
