#include <Arduino_FreeRTOS.h>

#define RED 7
#define YELLOW 6
#define GREEN 5

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler GreenLEDProfiler;

TaskHandle_t red_Handle,yellow_Handle,green_Handle;

int yellowTaskPrio;
int redTaskPrio;
int greenTaskPrio;

void setup()
{
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask,"RED Led Task",100,NULL,1,&red_Handle);
  xTaskCreate(yellowLedControllerTask,"Yellow Led Task",100,NULL,3,&yellow_Handle);
  xTaskCreate(greenLedControllerTask,"Green Led Task",100,NULL,1,&green_Handle);
}

void redLedControllerTask(void *pvParameters)
{
  while(1)
  {
//    RedLEDProfiler++;
//    Serial.print("Red run time : ");
//    Serial.println(RedLEDProfiler);
//    delay(100);
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  while(1)
  {
   // YellowLEDProfiler++;
    yellowTaskPrio = uxTaskPriorityGet(NULL);
    greenTaskPrio = uxTaskPriorityGet(green_Handle);
    Serial.print("Read green Task Priority : ");
    Serial.println(greenTaskPrio);
//    Serial.print("Yellow run time : ");
//    Serial.println(YellowLEDProfiler);
//    delay(100);
  }
}

void greenLedControllerTask(void *pvParameters)
{
  while(1)
  {
//    GreenLEDProfiler++;
//    Serial.print("Green Led run time : ");
//    Serial.println(GreenLEDProfiler);
//    delay(100);
  }
}
void loop()
{
  
}
