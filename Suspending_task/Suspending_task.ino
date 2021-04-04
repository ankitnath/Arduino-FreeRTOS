
#include<Arduino_FreeRTOS.h>
#define RED 7
#define YELLOW 6
#define GREEN 5

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler GreenLEDProfiler;

TaskHandle_t green_Handle,yellow_Handle,red_Handle;

uint32_t suspend_monitor;

void setup()
{
  
  Serial.begin(9600);
  xTaskCreate(redLEDControllerTask, //pointer to the function that implements the task
              "Red Led Task", //descriptive name of the task
              100, //it refers to stack depth and over here we can give values from 100-128 since Arduino has limited memory size
              NULL, //it refers to the parameter that is passed to the function
              1, //it refers to the priority & value ranges from 0-3 where 3 has the highest priority
              &red_Handle //refers to task handle
              //we cant give NULL to stack depth and priority
              );
   xTaskCreate(yellowLEDControllerTask,
               "Yellow LED Task",
               100,
               NULL,
               1,
               &yellow_Handle);

   xTaskCreate(greenLEDControllerTask,
               "green LED Task",
               100,
               NULL,
               1,
               &green_Handle);
                   
}


void redLEDControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);
  while(1)
  {
    digitalWrite(RED,digitalRead(RED)^1);
    RedLEDProfiler++;
    Serial.print("RED run time : ");
    Serial.println(RedLEDProfiler);
    vTaskDelay(100);
    
  }
}

void yellowLEDControllerTask(void *pvParameters)
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    YellowLEDProfiler++;
    Serial.print("Yellow run time : ");
    Serial.println(YellowLEDProfiler);
    
    if(suspend_monitor >= 30)
    {
      vTaskSuspend(yellow_Handle);
    }
    vTaskDelay(100);
    
  }
}

void greenLEDControllerTask(void *pvParameters)
{
  pinMode(GREEN,OUTPUT);
  while(1)
  {
    digitalWrite(GREEN,digitalRead(GREEN)^1);
    suspend_monitor++;
    GreenLEDProfiler++;
    Serial.print("Green run time : ");
    Serial.println(GreenLEDProfiler);
    vTaskDelay(100);
  }
}

void loop()
{
}
