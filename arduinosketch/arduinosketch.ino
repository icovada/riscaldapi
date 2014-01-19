#include <OneWire.h>

#define BAUDRATE 9600
#define RELAIS0 4
#define RELAIS1 5

OneWire ds(7);
byte insideTher[8] = { 
  0x28, 0xE, 0xF4, 0xAB, 0x4, 0x0, 0x0, 0x17 };
byte flowInTher[8] = { 
  0x28, 0x69, 0xED, 0xAB, 0x4, 0x0, 0x0, 0xDE };
byte flowOutTher[8] = { 
  0x28, 0xF7, 0x70, 0xAC, 0x4, 0x0, 0x0, 0xA1 };
byte insideRead[12];
byte flowInRead[12];
byte flowOutRead[12];
byte i;

void setup() {
  Serial.begin(BAUDRATE);
  pinMode(RELAIS0, OUTPUT);
  pinMode(RELAIS1, OUTPUT);
  digitalWrite(RELAIS0, 1);
  digitalWrite(RELAIS1, 1);
}

void loop() {

  calculateTemp(insideTher);
  calculateTemp(flowInTher);
  calculateTemp(flowOutTher);

  delay(1000);               // delay to calculate temperatures

  readTemp(insideTher);
  readTemp(flowInTher);
  readTemp(flowOutTher);

  if (Serial.available() > 0) {
    int inByte = Serial.read();
    switch (inByte) {
    case 'q':
      Serial.println("Relais 0 off");
      digitalWrite(RELAIS0, 1);
      break;

    case 'w':
      Serial.println("Relais 0 on");
      digitalWrite(RELAIS0, 0);
      break;

    case 'e':
      Serial.println("Relais 1 off");
      digitalWrite(RELAIS1, 1);
      break;

    case 'r':
      Serial.println("Relais 1 on");
      digitalWrite(RELAIS1, 0);
      break;

    case 't':
      Serial.println("Read and output sensor data");
      Serial.print("Inside = ");
      for ( i = 0; i < 9; i++) {           // we need 9 bytes
        Serial.print(insideRead[i], HEX);
        Serial.print(" ");
      }

      Serial.println();
      Serial.print("flowin = ");
      for ( i = 0; i < 9; i++) {           // we need 9 bytes
        Serial.print(flowInRead[i], HEX);
        Serial.print(" ");
      }

      Serial.println();
      Serial.print("flowout = ");
      for ( i = 0; i < 9; i++) {           // we need 9 bytes
        Serial.print(flowOutRead[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
      Serial.println();
      break;

    case 'y':
      Serial.println("Output relais status");
      Serial.print(!digitalRead(RELAIS0));
      Serial.print(", ");
      Serial.println(!digitalRead(RELAIS1));
      break;
    }
  }
}

void calculateTemp(byte *sensor) {
  ds.reset();
  ds.select(sensor);
  ds.write(0x44, 0);        // start conversion, without parasite power
}

float readTemp(byte *sensor){
  float result;
  byte tempRead[12];
  
  ds.reset();
  ds.select(sensor);
  ds.write(0xBE);          // read temperature
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    tempRead[i] = ds.read();
  }
  
  if (OneWire::crc8(tempRead, 8) == tempRead[9]){
    Serial.print("Right");
  } else {
    Serial.print("Wrong");
  }
  
  
  return result;
}

