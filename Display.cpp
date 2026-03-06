#include "Display.h"

// Initialize LCD address 0x27, 20 columns, 4 rows
LCD_I2C lcd(0x27, 20, 4);

void displayInit() {
  lcd.begin();
  lcd.clear();
  lcd.backlight();
}

void displayTime() {
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  lcd.print("__Vending Machines__");
  
  lcd.setCursor(0, 1);
  lcd.print("Time : ");
  
  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour());
  lcd.print(":");
  
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
  lcd.print(":");
  
  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second(), DEC);
  lcd.print("   ");
}

void displayLiquid(int liquidMl) {
  lcd.setCursor(0, 2);
  lcd.print("Amount: ");
  lcd.print(liquidMl);
  lcd.print(" ml.   ");
}

void displayPrice(int baths) {
  lcd.setCursor(0, 3);
  lcd.print("Money : ");
  lcd.print(baths);
  lcd.print(" Baht. ");
}

// Implement keypad reader
KeypadButton readKeypad() {
  int val = analogRead(PIN_KEYPAD);
  
  if (val <= 20) return BTN_SET;
  if (val >= 100 && val <= 200) return BTN_UP;
  if (val >= 300 && val <= 400) return BTN_DOWN;
  if (val >= 500 && val <= 600) return BTN_ENTER;
  if (val >= 700 && val <= 800) return BTN_CONF;
  
  return BTN_NONE;
}
