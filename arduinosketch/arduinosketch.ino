#define BAUDRATE 9600
#define RELAIS0 13
#define RELAIS1 8
#define ONEWIRE 10

void setup() {
  Serial.begin(BAUDRATE);
  // reserve 200 bytes for the inputString:
}

void loop() {
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    switch (inByte) {
      case 'a':
        Serial.println("Relais 0 off");
        digitalWrite(RELAIS0, LOW);
        break;

      case 'b':
        Serial.println("Relais 0 on");
        digitalWrite(RELAIS0, HIGH);
        break;

      case 'c':
        Serial.println("Relais 1 off");
        digitalWrite(RELAIS1, LOW);
        break;

      case 'd':
        Serial.println("Relais 1 on");
        digitalWrite(RELAIS0, HIGH);
        break;
        
      case 'e':
        Serial.println("Read and output sensor data");
        break;
        
      case 'f':
        Serial.println("Output relais status");
        break;
    }
  }
}
