#include <EEPROM.h>

//EEPROM Info
byte Earray[] = {100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200};
byte EIndex = 0;
byte Eaddr = 1;

void setup() {
  Serial.begin(9600);
  
  // NOTE: EEPROM.write only stores a single byte on AVR (0-255). 
  // 1000 will simply wrap. It should be EEPROM.put if it's an int.
  // Using EEPROM.put for 2-byte integer values to fix the syntax error.
  
  int val = 1000;
  
  EEPROM.put(0, val); // for 1 lites
  EEPROM.put(2, val); // for 2 lites
  EEPROM.put(4, val); // for 3 lites
  EEPROM.put(6, val); // for 4 lites
  EEPROM.put(8, val); // for 5 lites
  EEPROM.put(10, val); // for 6 lites
  EEPROM.put(12, val); // for 7 lites
  EEPROM.put(14, val); // for 8 lites
  
  Serial.println("EEPROM Basic Values Written Successfully.");
}

void loop() {
  // Empty loop
}
