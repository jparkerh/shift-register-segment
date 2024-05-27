/**
 * 7segment
 *
 */
#include "Arduino.h"

#define LATCH 2
#define CLK 12
#define DATA 13

void setup()
{
  // initialize drivers as output
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);

  Serial.begin(115200);
}

uint8_t digits[10] = {
  0xde,
  0x06,
  0xba,
  0xae,
  0x66,
  0xec,
  0xfc,
  0x86,
  0xfe,
  0xe6
};

void writeDigit(uint8_t digit) {
  Serial.println("digit: " + String(digit));
  for (int i=0; i<8; i++) {    
    digitalWrite(DATA, digit & 0x01);
    Serial.println(digit & 0x01);

    //shift one down
    digit = digit >> 1;
    delayMicroseconds(1000);
    digitalWrite(CLK, 1);
    delayMicroseconds(1000);
    digitalWrite(CLK, 0);
  }

  delayMicroseconds(1000);
  digitalWrite(LATCH, 1);
  delayMicroseconds(1000);
  digitalWrite(LATCH, 0);
}

void loop()
{
  for (int i = 0; i < 10; i++) {
    writeDigit(digits[i]);
    delay(500);
  }
}