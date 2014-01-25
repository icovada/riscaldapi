#include <OneWire.h>
#include <DallasTemperature.h>

#define BAUDRATE 9600
#define RELAIS0 4
#define RELAIS1 5

OneWire ds(7);
DallasTemperature sensors(&ds);

byte insideTher[8] = { 
  0x28, 0xE, 0xF4, 0xAB, 0x4, 0x0, 0x0, 0x17 };
byte flowInTher[8] = { 
  0x28, 0x69, 0xED, 0xAB, 0x4, 0x0, 0x0, 0xDE };
byte flowOutTher[8] = { 
  0x28, 0xF7, 0x70, 0xAC, 0x4, 0x0, 0x0, 0xA1 };
float insideRead;
float flowInRead;
float flowOutRead;
float goalTemp = 18;
float diffTemp = 0.2;
byte i;

void setup() {
  Serial.begin(BAUDRATE);
  pinMode(RELAIS0, OUTPUT);
  pinMode(RELAIS1, OUTPUT);
  digitalWrite(RELAIS0, 1);
  digitalWrite(RELAIS1, 1);
  
  //Set sensor resolution
  sensors.setResolution(insideTher, 12);
  sensors.setResolution(flowInTher, 11);
  sensors.setResolution(flowOutTher, 11);
  
}

void loop() {
  calculateTemp(insideTher);
  calculateTemp(flowInTher);
  calculateTemp(flowOutTher);

  delay(800);               // delay to calculate temperatures

  insideRead=readTemp(insideTher);
  flowInRead=readTemp(flowInTher);
  flowOutRead=readTemp(flowOutTher);

  // If relais off AND temperature is lower than (goal-diff) turn it on
  if ((!digitalRead(RELAIS0) == 0) && (insideRead < (goalTemp-diffTemp))){
    digitalWrite(RELAIS0, 0);
  }
    
  // If relais on AND temperature is higher than (goal+diff) turn it off
  if ((!digitalRead(RELAIS0) == 1) && (insideRead > (goalTemp+diffTemp))){
    digitalWrite(RELAIS0, 1);
  }

  if (Serial.available() > 0) {
    int inByte = Serial.read();
    switch (inByte) {
    case 'q':
      Serial.println("ACK");
      digitalWrite(RELAIS0, 1);
      break;

    case 'w':
      Serial.println("ACK");
      digitalWrite(RELAIS0, 0);
      break;

    case 'e':
      Serial.println("ACK");
      digitalWrite(RELAIS1, 1);
      break;

    case 'r':
      Serial.println("ACK");
      digitalWrite(RELAIS1, 0);
      break;

    case 't':
      Serial.print(insideRead);
      Serial.print(",");
      Serial.print(flowInRead);
      Serial.print(",");
      Serial.println(flowOutRead);
      break;

    case 'y':
      Serial.print(!digitalRead(RELAIS0));
      Serial.print(",");
      Serial.println(!digitalRead(RELAIS1));
      break;
    
    case 'u':        //manage inputs
      goalTemp=Serial.parseFloat();
      Serial.println(goalTemp);
      break;

    case 'i':
      diffTemp=Serial.parseFloat();
      Serial.println(diffTemp);
      break;
      
    case 'o':
      Serial.print(goalTemp);
      Serial.print(",");
      Serial.println(diffTemp);
    }
  }
}

void calculateTemp(byte *sensor) {
  ds.reset();
  ds.select(sensor);
  ds.write(0x44, 0);        // start conversion, without parasite power
  delay(250);
}

float readTemp(byte *sensor){
  float result;
  byte data[12];
  
  ds.reset();
  ds.select(sensor);
  ds.write(0xBE);          // read temperature
  delay(250);
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
   data[i] = ds.read();
  }
  
  if (OneWire::crc8(data, 8) != data[8]){   //Check CRC
    return (250); //If temperature read is wrong, return ludicrously high temp and keep relais off 
  }
  
  //////Code from library example sketch
  int16_t raw = (data[1] << 8) | data[0];
  return ((float)raw / 16.0);
}

