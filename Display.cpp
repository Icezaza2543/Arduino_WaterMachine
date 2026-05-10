#include "Display.h"

// Initialize LCD address 0x27, 20 columns, 4 rows
LCD_I2C lcd(0x27, 20, 4);

// Variables to keep track of last displayed values to prevent flicker
static int8_t lastHour = -1, lastMinute = -1, lastSecond = -1;
static uint16_t lastLiquid = 65535; // Unlikely initial value
static uint16_t lastBaths = 65535;  // Unlikely initial value
static unsigned long lastTimeCheck = 0;

void displayInit() {
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  
  // Print static UI elements once using F() to save SRAM
  lcd.setCursor(0, 0);
  lcd.print(F("   Vending Machine  ")); // Centered
  
  lcd.setCursor(0, 1);
  lcd.print(F("Time  : "));
  
  lcd.setCursor(0, 2);
  lcd.print(F("Amount:        ml."));
  
  lcd.setCursor(0, 3);
  lcd.print(F("Money :        Baht"));
}

void displayTime(bool force) {
  unsigned long currentMillis = millis();
  
  // To avoid hammering I2C, only read RTC every ~250ms or when forced
  if (force || currentMillis - lastTimeCheck >= 250) {
    lastTimeCheck = currentMillis;
    DateTime now = rtc.now();
    
    if (force || now.second() != lastSecond) {
      lcd.setCursor(8, 1);
      
      if (now.hour() < 10) lcd.print(F("0"));
      lcd.print(now.hour());
      lcd.print(F(":"));
      
      if (now.minute() < 10) lcd.print(F("0"));
      lcd.print(now.minute());
      lcd.print(F(":"));
      
      if (now.second() < 10) lcd.print(F("0"));
      lcd.print(now.second(), DEC);
      
      lastHour = now.hour();
      lastMinute = now.minute();
      lastSecond = now.second();
    }
  }
}

void displayLiquid(uint16_t liquidMl, bool force) {
  if (force || liquidMl != lastLiquid) {
    lcd.setCursor(8, 2);
    lcd.print(F("      ")); // Clear up to 6 spaces
    lcd.setCursor(8, 2);
    lcd.print(liquidMl);
    lastLiquid = liquidMl;
  }
}

void displayPrice(uint16_t baths, bool force) {
  if (force || baths != lastBaths) {
    lcd.setCursor(8, 3);
    lcd.print(F("      ")); // Clear up to 6 spaces
    lcd.setCursor(8, 3);
    lcd.print(baths);
    lastBaths = baths;
  }
}

// Implement keypad reader
KeypadButton readKeypad() {
  int val = analogRead(PIN_KEYPAD);
  
  // Note: Thresholds may need to be adjusted based on the specific keypad resistor values
  if (val <= 20) return BTN_SET;
  if (val >= 100 && val <= 200) return BTN_UP;
  if (val >= 300 && val <= 400) return BTN_DOWN;
  if (val >= 500 && val <= 600) return BTN_ENTER;
  if (val >= 700 && val <= 800) return BTN_CONF;
  
  return BTN_NONE;
}
