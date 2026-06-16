#include <Arduino.h>
#include <TLE75080.h>
#include <LibPrintf.h>


TLE75080 *tle;

void printBinary(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        printf("%c", (value & (1 << i)) ? '1' : '0');
    }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  printf("TLE75080 demo\n");

  tle = new TLE75080(5, 4);
  tle->begin();

  printf("INST frame: 0x%04X\n", tle->readInst());

  printf("STD_DIAG frame: 0x%04X\n", tle->readDiag());
  
  printf("OUTPUT frame: 0x%04X\n", tle->readOutputs());
  
}

void loop() {
  if (tle->out > 0x08) {
    tle->out = (tle->out << 1);
  } else {
    tle->out = (tle->out << 1) | 1;
  }
  tle->update();

  printf("OUTPUT frame: ");
  printBinary(tle->readOutputs());
  printf("\n");

  printf("STD_DIAG frame: 0x%04X\n", tle->readDiag());

  delay(1000);
}
