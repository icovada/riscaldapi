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
float insideRead;
float flowInRead;
float flowOutRead;
float goalTemp = 18;
float diffTemp = 0.3;
byte i;

void setup() {
  Serial.begin(BAUDRATE);
  pinMode(RELAIS0, OUTPUT);
  pinMode(RELAIS1, OUTPUT);
  digitalWrite(RELAIS0, 1);
  digitalWrite(RELAIS1, 1);
}

void loop() {

  Serial.println(goalTemp);
  Serial.println(diffTemp);
    
  calculateTemp(insideTher);
  calculateTemp(flowInTher);
  calculateTemp(flowOutTher);

  delay(600);               // delay to calculate temperatures

  insideRead=readTemp(insideTher);
  flowInRead=readTemp(flowInTher);
  flowOutRead=readTemp(flowOutTher);

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
      Serial.print(insideRead);
      

      Serial.println();
      Serial.print("flowin = ");
      Serial.print(flowInRead);
      

      Serial.println();
      Serial.print("flowout = ");
      Serial.print(flowOutRead);

      Serial.println();
      Serial.println();
      break;

    case 'y':
      Serial.println("Output relais status");
      Serial.print(!digitalRead(RELAIS0));
      Serial.print(", ");
      Serial.println(!digitalRead(RELAIS1));
      break;
    
    case 'u':        //manage inputs
      goalTemp=Serial.parseFloat();

    case 'd':
      diffTemp=Serial.parseFloat();
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
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
   data[i] = ds.read();
  }
  
  if (OneWire::crc8(data, 8) != data[8]){   //Check CRC
    return (-100);
  }
  
  //////Code from library example sketch
  int16_t raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
  // at lower res, the low bits are undefined, so let's zero them
  if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
  else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
  else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  //// default is 12 bit resolution, 750 ms conversion time
  return (float)raw / 16.0;
}

