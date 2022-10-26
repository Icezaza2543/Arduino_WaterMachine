int tankvalue = 5000;
int leftvalue;
int current_used_value = 0;

void ESP01()
{
  //check realtime tank value
  while(tankvalue != current_used_value)
  {
    leftvalue = tankvalue - current_used_value;
    //send data
    Serial.write(leftvalue);
  }
}
