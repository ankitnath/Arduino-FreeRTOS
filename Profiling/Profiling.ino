#include <Arduino_FreeRTOS.h>

#define GREEN 7
#define YELLOW 6
#define WHITE 5


typedef int TaskProfiler;

TaskProfiler GreenLedProfiler;
TaskProfiler YellowLedProfiler;
TaskProfiler WhiteLedProfiler;
void setup()
{
  Serial.begin(9600);
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
    GreenLedProfiler++;
    Serial.print("GreenLedProfiler : ");
    Serial.println(GreenLedProfiler);
  //  digitalWrite(GREEN,digitalRead(GREEN)^1);
  delay(300);
  }
}

void yellowLedControllerTask(void *pvparameters) //pv--> pointer to void
{
  
  pinMode(YELLOW,OUTPUT); 
  //or use infinite for loop
  while(1)
  {
    YellowLedProfiler++;
    Serial.print("YellowLedProfiler : ");
    Serial.println(YellowLedProfiler);
  //  digitalWrite(YELLOW,digitalRead(YELLOW)^1);
  delay(300);
  }
}

void whiteLedControllerTask(void *pvparameters) //pv--> pointer to void
{
  pinMode(WHITE,OUTPUT);
  //or use infinite for loop
  while(1)
  {
    WhiteLedProfiler++;
    Serial.print("WhiteLedProfiler : ");
    Serial.println(WhiteLedProfiler);
  //  digitalWrite(WHITE,digitalRead(WHITE)^1); 
  delay(300);
  }
}

void loop()
{
//     digitalWrite(GREEN,digitalRead(GREEN)^1);
//     digitalWrite(YELLOW,digitalRead(YELLOW)^1);
//     digitalWrite(WHITE,digitalRead(WHITE)^1);
//     delay(50);
}
