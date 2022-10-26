#include "LCD.h"

void setup()
{
  //  ---------Module---------
  Serial.begin(57600); 
  Wire.begin(); 
  rtc.begin(); 
  lcd.begin(); // กำหนดเชื่อมต่อจอ 16ตัวอักษร 2 แถว  
  lcd.clear();
  lcd.backlight();
  //EEPROM.put(0, void data());
  Coin_data = EEPROM.read(0);
  //  --------- I/O ---------
  pinMode(R[0], OUTPUT);
  pinMode(R[1], OUTPUT);  
  pinMode(R[2], OUTPUT);  
  pinMode(R[3], OUTPUT);      
  pinMode(sw, INPUT_PULLUP);
  pinMode(keypadPin, INPUT);
  pinMode(coinpin, INPUT_PULLUP);
  //--------- Coin Accepter ---------
  attachInterrupt(digitalPinToInterrupt(coinpin), coinInterrupt, RISING); // code นับเหรียญ +1 +2 +5 +10 
  //--------- Time ---------
  if (rtc.lostPower()) 
  {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  DateTime now = rtc.now();
  //----- set initial relay state -----
  digitalWrite(R[0],0);
  digitalWrite(R[1],0);
  digitalWrite(R[2],0);
  digitalWrite(R[3],0);
}

void coinInterrupt()
{
  digitalWrite(R[1],1); //R[1]=status_light
  //attachInterrupt(digitalPinToInterrupt(sw),turn_on_relay, HIGH);
  int Baths = 0;
  int liquid = 0;
  /*
  EEPROM.read
  while(digitalRead(sw)==HIGH)
  turn_on_relay();
  unsigned long int startTime = millis();
  {
    if(currentTime - startTime  >= 10b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 20b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 30b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 40b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 50b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 60b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 70b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 80b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 90b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 100b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 110b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 120b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 130b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 140b) {digitalWrite(R[3],LOW)}
    else if(currentTime - startTime  >= 150b) {digitalWrite(R[3],LOW)}

  /*
  #define 1 liter = 5000 millis();
  //turn money to time 
  liters = Baths*1000;

  if(millis(); >= Baths)
  {
    digitalWrite(R[3],LOW);
  }
  
  
  */
}

void loop()
{
  DateTime now = rtc.now();
  lcdtime();
  lcdliquid(liquid);
  lcdprice(Baths);
  coinInterrupt();
  conf();
  
  if (now.hour() == 18 && now.minute() == 00 )
  {
    digitalWrite(R[0],1); //R[0]=front_light
  }
  else if(now.hour() == 6 && now.minute() == 00 );
  {
    digitalWrite(R[0],0);
  }
  
  //Coincheck    
  Serial.print(" Baths ");  
  delay(1000);  
}
