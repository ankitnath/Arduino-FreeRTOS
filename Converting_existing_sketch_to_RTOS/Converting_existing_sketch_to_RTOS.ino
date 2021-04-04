#include <Arduino_FreeRTOS.h>

#define GREEN 7
#define YELLOW 6
#define WHITE 5

void setup()
{
  
  //create a task

  xTaskCreate(greenLedControllerTask,"GREEN LED Task",128,NULL,1,NULL);
  xTaskCreate(yellowLedControllerTask,"YELLOW LED Task",128,NULL,1,NULL);
  xTaskCreate(whiteLedControllerTask,"WHITE LED Task",128,NULL,1,NULL);
}

void greenLedControllerTask(void *pvparameters) //pv--> pointer to void
{
   pinMode(GREEN,OUTPUT);
  //or use infinite for loop
  while(1)
  {
    digitalWrite(GREEN,digitalRead(GREEN)^1);
  }
}

void yellowLedControllerTask(void *pvparameters) //pv--> pointer to void
{
  pinMode(YELLOW,OUTPUT);
  //or use infinite for loop
  while(1)
  {
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
  }
}

void whiteLedControllerTask(void *pvparameters) //pv--> pointer to void
{
  pinMode(WHITE,OUTPUT);
  //or use infinite for loop
  while(1)
  {
    digitalWrite(WHITE,digitalRead(WHITE)^1); 
  }
}

void loop()
{
//     digitalWrite(GREEN,digitalRead(GREEN)^1);
//     digitalWrite(YELLOW,digitalRead(YELLOW)^1);
//     digitalWrite(WHITE,digitalRead(WHITE)^1);
//     delay(50);
}
