#include<Arduino_FreeRTOS.h>

#define GREEN 7
#define YELLOW 6
#define RED 5

typedef int TaskProfiler;

TaskProfiler GreenLedProfiler;
TaskProfiler YellowLedProfiler;
TaskProfiler RedLedProfiler;

TaskHandle_t green_Handle,yellow_Handle,red_Handle;

 void setup()
 {

  xTaskCreate(greenLedControllerTask, "Green Led Task",100,NULL,1,&green_Handle);
  xTaskCreate(yellowLedControllerTask, "Yellow Led Task",100,NULL,1,&yellow_Handle);
  xTaskCreate(redLedControllerTask, "Red Led Task",100,NULL,1,&red_Handle);
  
 }

void greenLedControllerTask(void *pvParameters)
{ 
  pinMode(GREEN,OUTPUT);
  while(1)
  {
    digitalWrite(GREEN,digitalRead(GREEN)^1);
    vTaskDelay(200/portTICK_PERIOD_MS);
    
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    vTaskDelay(300/portTICK_PERIOD_MS);
   
  }
}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);
  while(1)
  {
    digitalWrite(RED,digitalRead(RED)^1);
    vTaskPrioritySet(green_Handle,2);
   vTaskDelay(500/portTICK_PERIOD_MS);
   
   
  }
}

void loop()
{
}
