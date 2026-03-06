/*
 * Bas on Tech - LONG PRESS BUTTON
 * This course is part of the courses on https://arduino-tutorials.net
 */

//// SWITCH ////
static const int buttonPin = 12;                    // switch pin
int buttonStatePrevious = LOW;                      // previousstate of the switch

unsigned long minButtonLongPressDuration = 3000;    // Time we wait before we see the press as a long press
unsigned long buttonLongPressMillis;                // Time in ms when we the button was pressed
bool buttonStateLongPress = false;                  // True if it is a long press

const int intervalButton = 50;                      // Time between two readings of the button state
unsigned long previousButtonMillis;                 // Timestamp of the latest reading

unsigned long buttonPressDuration;                  // Time the button is pressed in ms

//// GENERAL ////
unsigned long currentMillis;          // Variabele to store the number of milleseconds since the Arduino has started

void setup() {
  Serial.begin(9600);                 // Initialise the serial monitor
  pinMode(buttonPin, INPUT);          // set buttonPin as input
  Serial.println("Press button");
}

void readButtonState() {
  if (currentMillis - previousButtonMillis > intervalButton) {
    int buttonState = digitalRead(buttonPin);    

    if (buttonState == HIGH && buttonStatePrevious == LOW && !buttonStateLongPress) {
      buttonLongPressMillis = currentMillis;
      buttonStatePrevious = HIGH;
      Serial.println("Button pressed");
    }

    buttonPressDuration = currentMillis - buttonLongPressMillis;

    if (buttonState == HIGH && !buttonStateLongPress && buttonPressDuration >= minButtonLongPressDuration) {
      buttonStateLongPress = true;
      Serial.println("Button long pressed");
    }
      
    if (buttonState == LOW && buttonStatePrevious == HIGH) {
      buttonStatePrevious = LOW;
      buttonStateLongPress = false;
      Serial.println("Button released");
      
      if (buttonPressDuration < minButtonLongPressDuration) {
        Serial.println("Button pressed shortly");
      }
    }
    previousButtonMillis = currentMillis;
  }
}

void loop() {
  currentMillis = millis();    // store the current time
  readButtonState();           // read the button state
}
