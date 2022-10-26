#include <EEPROM.h>

//EEPROM Info
byte Earray[] = {100 , 110 , 120 ,130 ,140 ,150 ,160 ,170 ,180 ,190 ,200}
byte EIndex = 0;
byte Eaddr = 1;

void setup()
{
  EEPROM.write(0, 1000) //for 1 lites
  EEPROM.write(1, 1000) //for 2 lites
  EEPROM.write(2, 1000) //for 3 lites
  EEPROM.write(3, 1000) //for 4 lites
  EEPROM.write(4, 1000) //for 5 lites
  EEPROM.write(5, 1000) //for 6 lites
  EEPROM.write(6, 1000) //for 7 lites
  EEPROM.write(7, 1000) //for 8 lites
}
void loop()
{

}