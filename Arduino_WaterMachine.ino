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
SoftwareSerial espSerial(PIN_ESP_RX, PIN_ESP_TX); // RX=5, TX=6

volatile uint16_t totalBaths = 0;
volatile unsigned long dispenseTimeRemaining = 0;
volatile bool isCoinInserted = false;
volatile bool isDispenseRequested = false;

uint16_t currentLiquidAmount = 0;
uint16_t currentUsedValue = 0;
uint16_t tankLeftValue = MAX_TANK_CAPACITY;

unsigned long pumpStartTime = 0;
bool isPumpActive = false;

unsigned long coinStatusLightOnTime = 0;
bool isCoinLightOn = false;
const unsigned long COIN_LIGHT_DURATION = 500; // MS to keep light on after coin

bool isFrontLightOn = false;

// --------------------- Interrupt Service Routines ---------------------
void onCoinInserted() {
  isCoinInserted = true;
}

void onDispenseButtonPressed() {
  isDispenseRequested = true;
}

// --------------------- Main Setup ---------------------
void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  Wire.begin();
  
  if (!rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  displayInit();
  displayTime(true);
  displayLiquid(currentLiquidAmount, true);
  displayPrice(totalBaths, true);

  // Define I/O Pins
  pinMode(PIN_RELAY_FRONT_LIGHT, OUTPUT);
  pinMode(PIN_RELAY_STATUS_LIGHT, OUTPUT);
  pinMode(PIN_RELAY_FLOAT_LIGHT, OUTPUT);
  pinMode(PIN_RELAY_PUMP, OUTPUT);
  
  pinMode(PIN_COIN_ACCEPTOR, INPUT_PULLUP);
  pinMode(PIN_BUTTON_DISPENSE, INPUT_PULLUP);
  pinMode(PIN_KEYPAD, INPUT);

  // Initialize Relays (Active LOW assumed as safe OFF state)
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

  // 1. Process Inserted Coins
  if (isCoinInserted) {
    noInterrupts();
    isCoinInserted = false; // Reset flag safely
    interrupts();

    totalBaths += 1; 
    currentLiquidAmount = totalBaths * 1000; // Example: 1 Baht = 1000 ml
    dispenseTimeRemaining = totalBaths * MILLIS_PER_LITER; // Example: 1 Baht = 5 seconds

    if (!isCoinLightOn) {
      digitalWrite(PIN_RELAY_STATUS_LIGHT, HIGH); // Temporary status indicator
      isCoinLightOn = true;
    }
    coinStatusLightOnTime = currentMillis;
    Serial.print(F("Coin inserted. Total: "));
    Serial.println(totalBaths);
  }

  // Turn off coin status light after duration without blocking
  if (isCoinLightOn && (currentMillis - coinStatusLightOnTime >= COIN_LIGHT_DURATION)) {
    digitalWrite(PIN_RELAY_STATUS_LIGHT, LOW);
    isCoinLightOn = false;
  }

  // 2. Process Dispense Request (Non-blocking)
  if (isDispenseRequested) {
    noInterrupts();
    isDispenseRequested = false; // Reset flag safely
    interrupts();

    if (totalBaths > 0 && !isPumpActive) {
      isPumpActive = true;
      pumpStartTime = currentMillis;
      
      digitalWrite(PIN_RELAY_PUMP, HIGH); // Turn ON pump
      Serial.println(F("Dispensing Started..."));
    }
  }

  // 3. Handle Active Pump Dispensing
  if (isPumpActive) {
    if ((currentMillis - pumpStartTime) >= dispenseTimeRemaining) {
      // Dispensing Finished
      digitalWrite(PIN_RELAY_PUMP, LOW); // Turn OFF pump
      isPumpActive = false;
      
      // Update Tank
      currentUsedValue += currentLiquidAmount;
      if (currentUsedValue > MAX_TANK_CAPACITY) currentUsedValue = MAX_TANK_CAPACITY;

      // Reset values
      totalBaths = 0;
      currentLiquidAmount = 0;
      dispenseTimeRemaining = 0;
      Serial.println(F("Dispensing complete."));
      
      // Force display update
      displayLiquid(currentLiquidAmount, true);
      displayPrice(totalBaths, true);
    }
  }

  // 4. Update Time-based Lighting (18:00 ON, 06:00 OFF)
  static unsigned long lastRtcCheck = 0;
  if (currentMillis - lastRtcCheck >= 1000) {
    lastRtcCheck = currentMillis;
    DateTime now = rtc.now();
    
    bool shouldBeOn = (now.hour() >= 18 || now.hour() < 6);
    if (shouldBeOn && !isFrontLightOn) {
      digitalWrite(PIN_RELAY_FRONT_LIGHT, HIGH);
      isFrontLightOn = true;
    } else if (!shouldBeOn && isFrontLightOn) {
      digitalWrite(PIN_RELAY_FRONT_LIGHT, LOW);
      isFrontLightOn = false;
    }
  }

  // 5. Check Configuration Keypad
  KeypadButton pressedKey = readKeypad();
  if (pressedKey == BTN_CONF) {
    Serial.println(F("Config mode selected."));
  }

  // 6. Update LCD Display (Smart rendering without delay)
  displayTime();
  displayLiquid(currentLiquidAmount);
  displayPrice(totalBaths);

  // 7. Send Real-time tank data to ESP-01
  static unsigned long lastEspSync = 0;
  if (currentMillis - lastEspSync >= 5000) { // Sync every 5s
    lastEspSync = currentMillis;
    int16_t leftValue = tankLeftValue - currentUsedValue;
    if (leftValue < 0) leftValue = 0;
    
    // Send data to ESP-01 via SoftwareSerial
    espSerial.print(F("TANK:"));
    espSerial.println(leftValue);
  }
}

