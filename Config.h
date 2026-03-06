#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// -------------------------- PIN Definitions --------------------------
const int PIN_RELAY_FRONT_LIGHT = 10;
const int PIN_RELAY_STATUS_LIGHT = 11;
const int PIN_RELAY_FLOAT_LIGHT = 12; // Unused in main flow, but defined
const int PIN_RELAY_PUMP = 13;

const int PIN_COIN_ACCEPTOR = 3;      // Interrupt 1
const int PIN_BUTTON_DISPENSE = 2;    // Interrupt 0 / Push Button
const int PIN_FEED = 4;
const int PIN_KEYPAD = A1;

// -------------------------- System Constants --------------------------
const int MAX_TANK_CAPACITY = 5000;
const int MILLIS_PER_LITER = 5000;    // 1 Liter = 5 Seconds pump time

// -------------------------- Global Variables --------------------------
extern volatile int totalBaths;       // Money accumulated
extern volatile unsigned long dispenseTimeRemaining;
extern volatile bool isCoinInserted;
extern volatile bool isDispenseRequested;

extern int currentLiquidAmount;       // Display purpose
extern int currentUsedValue;          // Water consumption tracker
extern int tankLeftValue;             // Remaining water

// -------------------------- Keypad Definitions --------------------------
enum KeypadButton {
  BTN_NONE = 0,
  BTN_SET = 1,
  BTN_UP = 2,
  BTN_DOWN = 3,
  BTN_ENTER = 4,
  BTN_CONF = 5
};

KeypadButton readKeypad();

#endif // CONFIG_H
