#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// -------------------------- PIN Definitions --------------------------
const uint8_t PIN_RELAY_FRONT_LIGHT = 10;
const uint8_t PIN_RELAY_STATUS_LIGHT = 11;
const uint8_t PIN_RELAY_FLOAT_LIGHT = 12; // Unused in main flow, but defined
const uint8_t PIN_RELAY_PUMP = 13;

const uint8_t PIN_COIN_ACCEPTOR = 3;      // Interrupt 1
const uint8_t PIN_BUTTON_DISPENSE = 2;    // Interrupt 0 / Push Button
const uint8_t PIN_FEED = 4;
const uint8_t PIN_KEYPAD = A1;

// ESP-01 Serial Pins
const uint8_t PIN_ESP_RX = 5;
const uint8_t PIN_ESP_TX = 6;

// -------------------------- System Constants --------------------------
const uint16_t MAX_TANK_CAPACITY = 5000;
const uint16_t MILLIS_PER_LITER = 5000;    // 1 Liter = 5 Seconds pump time

// -------------------------- Global Variables --------------------------
extern volatile uint16_t totalBaths;       // Money accumulated
extern volatile unsigned long dispenseTimeRemaining;
extern volatile bool isCoinInserted;
extern volatile bool isDispenseRequested;

extern uint16_t currentLiquidAmount;       // Display purpose
extern uint16_t currentUsedValue;          // Water consumption tracker
extern uint16_t tankLeftValue;             // Remaining water

// -------------------------- Keypad Definitions --------------------------
enum KeypadButton : uint8_t {
  BTN_NONE = 0,
  BTN_SET = 1,
  BTN_UP = 2,
  BTN_DOWN = 3,
  BTN_ENTER = 4,
  BTN_CONF = 5
};

KeypadButton readKeypad();

#endif // CONFIG_H
