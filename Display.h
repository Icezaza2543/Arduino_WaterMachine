#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <RTClib.h>
#include <LCD_I2C.h>
#include "Config.h"

// Define LCD and RTC objects externally so main can use them
extern LCD_I2C lcd;
extern RTC_DS3231 rtc;

// Function Prototypes
void displayInit();
void displayTime();
void displayLiquid(int liquidMl);
void displayPrice(int baths);

#endif // DISPLAY_H
