#import <OneWire.h>

#define BAUDRATE 9600
#define RELAIS0 4
#define RELAIS1 5

OneWire ds(7);

void setup() {
  Serial.begin(BAUDRATE);
  pinMode(RELAIS0, OUTPUT);
  pinMode(RELAIS1, OUTPUT);
  digitalWrite(RELAIS0, 1);
  digitalWrite(RELAIS1, 1);
}

void loop() {
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
