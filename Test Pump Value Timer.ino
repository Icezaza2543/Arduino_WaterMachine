#include <EEPROM.h>
#include <Wire.h> 
#include <SPI.h>
#include <RTClib.h> 
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 20, 4);
RTC_DS3231 rtc;

//--------------------------PIN Define------------------------ 
int R[] = {4,5,6,7};
int sw1 = 13;
int sw2 = 10;

//---------------------------CONT Define-------------------------
unsigned long int timer = 0;
unsigned long int i_timer = millis();
unsigned long int s_timer;

void setup()
{
  //  ------------------------Module----------------------------------
  Serial.begin(115200); 
  Wire.begin(); 
  rtc.begin(); 
  lcd.begin(); // กำหนดเชื่อมต่อจอ 16ตัวอักษร 2 แถว  
  lcd.clear();
  lcd.backlight();
  //  --------- I/O ---------
  pinMode(R[0], OUTPUT);
  pinMode(R[1], OUTPUT);  
  pinMode(R[2], OUTPUT);  
  pinMode(R[3], OUTPUT);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  
  //--------- Time ---------
  if (rtc.lostPower()) 
  {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  DateTime now = rtc.now();
  //----- set initial relay state -----
  digitalWrite(R[0],1);
  digitalWrite(R[1],1);
  digitalWrite(R[2],1);
  digitalWrite(R[3],1);
}

void checkUp()
{
  while(1) {
  if(digitalRead(sw1) == LOW)
  {
    i_timer = millis();
    while(digitalRead(sw2) == HIGH)
    {
      s_timer = millis();
      digitalWrite(R[0],0);
      timer = (s_timer - i_timer);
      lcd.setCursor(7,1);
      lcd.print(timer);
      lcd.setCursor(14,1);
      lcd.print("Ms");

      if(digitalRead(sw2)==LOW)
      {
        while(digitalRead(sw1)==HIGH)
        {
          digitalWrite(R[0],1);
          lcd.setCursor(0,2);
          lcd.print("Counter: ");
          lcd.setCursor(8,2);
          lcd.print(timer);
          Serial.write(timer);
          delay(100);
        }
      }
    }
    }
  }
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("__Vending Machines__");
  lcd.setCursor(0, 1);
  lcd.print("Time :");
  checkUp();
}


