/**
 * Arduino Water Vending Machine
 * Cleaned and Optimized Code
 */

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include <RTClib.h>
#include <SoftwareSerial.h>

#include "Config.h"
#include "Display.h"

// --------------------- Global Variables Init ---------------------
RTC_DS3231 rtc;
SoftwareSerial espSerial(0, 1); // RX, TX for ESP-01

volatile int totalBaths = 0;
volatile unsigned long dispenseTimeRemaining = 0;
volatile bool isCoinInserted = false;
volatile bool isDispenseRequested = false;

int currentLiquidAmount = 0;
int currentUsedValue = 0;
int tankLeftValue = MAX_TANK_CAPACITY;

unsigned long pumpStartTime = 0;
bool isPumpActive = false;

// --------------------- Interrupt Service Routines ---------------------
void onCoinInserted() {
  // Simple interrupt routine to flag coin insertion
  // Debouncing is assumed to be handled by the coin acceptor hardware
  isCoinInserted = true;
}

void onDispenseButtonPressed() {
  // Flag that the user requested dispensing
  isDispenseRequested = true;
}

// --------------------- Main Setup ---------------------
void setup() {
  Serial.begin(57600);
  espSerial.begin(9600);
  Wire.begin();
  
  displayInit();
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Define I/O Pins
  pinMode(PIN_RELAY_FRONT_LIGHT, OUTPUT);
  pinMode(PIN_RELAY_STATUS_LIGHT, OUTPUT);
  pinMode(PIN_RELAY_FLOAT_LIGHT, OUTPUT);
  pinMode(PIN_RELAY_PUMP, OUTPUT);
  
  pinMode(PIN_COIN_ACCEPTOR, INPUT_PULLUP);
  pinMode(PIN_BUTTON_DISPENSE, INPUT_PULLUP);
  pinMode(PIN_KEYPAD, INPUT);

  // Initialize Relays (Active LOW assumed, but original code initialized them to 0 and 1 variously. Set safe OFF state = LOW for now)
  digitalWrite(PIN_RELAY_FRONT_LIGHT, LOW);
  digitalWrite(PIN_RELAY_STATUS_LIGHT, LOW);
  digitalWrite(PIN_RELAY_FLOAT_LIGHT, LOW);
  digitalWrite(PIN_RELAY_PUMP, LOW);

  // Attach Interrupts
  attachInterrupt(digitalPinToInterrupt(PIN_COIN_ACCEPTOR), onCoinInserted, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_DISPENSE), onDispenseButtonPressed, FALLING);

  // Example: Read starting coin count from EEPROM if needed
  // EEPROM.get(0, totalBaths);
}

// --------------------- Main Loop ---------------------
void loop() {
  unsigned long currentMillis = millis();
  DateTime now = rtc.now();

  // 1. Process Inserted Coins
  if (isCoinInserted) {
    totalBaths += 1; // Or read logic based on pulse count
    currentLiquidAmount = totalBaths * 1000; // Example: 1 Baht = 1000 ml
    dispenseTimeRemaining = totalBaths * MILLIS_PER_LITER; // Example: 1 Baht = 5 seconds

    isCoinInserted = false; // Reset flag
    digitalWrite(PIN_RELAY_STATUS_LIGHT, HIGH); // Temporary status indicator
  } else {
    digitalWrite(PIN_RELAY_STATUS_LIGHT, LOW);
  }

  // 2. Process Dispense Request (Non-blocking)
  if (isDispenseRequested && totalBaths > 0 && !isPumpActive) {
    isPumpActive = true;
    pumpStartTime = currentMillis;
    isDispenseRequested = false;
    
    digitalWrite(PIN_RELAY_PUMP, HIGH); // Turn ON pump
    Serial.println("Dispensing Started...");
  }

  // 3. Handle Active Pump Dispensing
  if (isPumpActive) {
    if ((currentMillis - pumpStartTime) >= dispenseTimeRemaining) {
      // Dispensing Finished
      digitalWrite(PIN_RELAY_PUMP, LOW); // Turn OFF pump
      isPumpActive = false;
      
      // Reset values
      totalBaths = 0;
      currentLiquidAmount = 0;
      dispenseTimeRemaining = 0;
      Serial.println("Dispensing complete.");
    }
  }

  // 4. Update Time-based Lighting (18:00 ON, 06:00 OFF)
  if (now.hour() >= 18 || now.hour() < 6) {
    digitalWrite(PIN_RELAY_FRONT_LIGHT, HIGH);
  } else {
    digitalWrite(PIN_RELAY_FRONT_LIGHT, LOW);
  }

  // 5. Check Configuration Keypad
  KeypadButton pressedKey = readKeypad();
  if (pressedKey == BTN_CONF) {
    Serial.println("Config mode selected.");
  }

  // 6. Update LCD Display (Non-blocking delay can be added if it flickers)
  displayTime();
  displayLiquid(currentLiquidAmount);
  displayPrice(totalBaths);

  // 7. Send Real-time tank data to ESP-01
  if (tankLeftValue != currentUsedValue) {
    int leftValue = tankLeftValue - currentUsedValue;
    espSerial.write(leftValue); // Send actual bytes or format string
  }

  delay(200); // Prevent LCD flicker and CPU hogging
}
