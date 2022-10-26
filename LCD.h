#include <RTClib.h> 
#include <LCD_I2C.h>
#include <Wire.h> 
#include <SPI.h>
#include <EEPROM.h>
#include "CONF.h"
#include <SoftwareSerial.h>

LCD_I2C lcd(0x27, 20, 4);
RTC_DS3231 rtc;
SoftwareSerial mySerial (0, 1);

//--PIN Define-- 
int R[] = {10,11,12,13}; // 0.front_light 1.status_light 2.floting_light 3.pump
int coinpin = 3;//interupt_1
int feed = 4;
byte Coin_data;
int sw = 2;//interupt_2

//--CONT Define--
int Baths = 0;
int liquid = 0;

//--config button for AD_KEYBOARD--
const byte keypadPin = A1;
byte key = 0;
const byte NONE = 0;
const byte set_btn = 1;
const byte up_btn = 2;
const byte down_btn = 3;
const byte enter_btn = 4;
const byte conf_btn = 5;

void lcdtime()
{
  DateTime now = rtc.now();
  lcd.setCursor(0,0);
  lcd.print("__Vending Machines__");
  lcd.setCursor(0, 1);
  lcd.print("Time :"); 
  lcd.setCursor(7,1); 
  lcd.print(now.hour()); 
  lcd.setCursor(9,1); 
  lcd.print(":"); 
  lcd.setCursor(10,1); 
  lcd.print(now.minute()); 
  lcd.setCursor(12,1); 
  lcd.print(":"); 
  lcd.setCursor(13,1); 
  lcd.print(now.second(),DEC); 
  lcd.setCursor(15,1); 
  lcd.print(" ");
}

void lcdliquid(const int liquid)
{
  lcd.setCursor(16,1);
  lcd.print("m.");
  lcd.setCursor(0,2);
  lcd.print("Amount:");
  lcd.setCursor(9,2);
  lcd.print(liquid);
  lcd.setCursor(12,2);
  lcd.print("ml.");
}

void lcdprice(const int Baths)
{ 
  lcd.setCursor(0,3);
  lcd.print("Money : ");
  lcd.setCursor(9,3);
  lcd.print(Baths);
  lcd.setCursor(12,3);
  lcd.print("Baths.");
}

byte getKey()
{
  int val = 0;
  byte button = 0;
  val = analogRead(keypadPin);
  button = NONE;
  if (val <= 20) { button = set_btn;}
  else if ( (val >= 100) && (val <= 200) ) { button = up_btn; }
  else if ( (val >= 300) && (val <= 400) ) { button = down_btn; }
  else if ( (val >= 500) && (val <= 600) ) { button = enter_btn; }
  else if ( (val >= 700) && (val <= 800) ) { button = conf_btn; }
  return button;
}

void conf()
{
  key = getKey();
  if (key==conf_btn) 
  {
    Serial.println("Enter Config mode");
    if (key==set_btn) {Serial.println("set btn");}
    if (key==up_btn) {Serial.println("up btn");}
    if (key==down_btn) {Serial.println("down btn");}
    if (key==enter_btn) {Serial.println("enter btn");}
  
  }

}