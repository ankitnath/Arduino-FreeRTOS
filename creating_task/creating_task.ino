
#include<Arduino_FreeRTOS.h>
#define GREEN 7
#define YELLOW 6
#define WHITE 5

typedef int TaskProfiler;

TaskProfiler GreenLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler WhiteLEDProfiler;

void setup()
{
  Serial.begin(9600);
  xTaskCreate(greenLEDControllerTask, //pointer to the function that implements the task
              "Red Led Task", //descriptive name of the task
              100, //it refers to stack depth and over here we can give values from 100-128 since Arduino has limited memory size
              NULL, //it refers to the parameter that is passed to the function
              1, //it refers to the priority & value ranges from 0-3 where 3 has the highest priority
              NULL //refers to task handle

              //we cant give NULL to stack depth and priority
              );
   xTaskCreate(yellowLEDControllerTask,
               "Yellow LED Task",
               100,
               NULL,
               1,
               NULL);

   xTaskCreate(whiteLEDControllerTask,
               "White LED Task",
               100,
               NULL,
               1,
               NULL);
               
     
}


void greenLEDControllerTask(void *pvParameters)
{
  pinMode(GREEN,OUTPUT);
  while(1)
  {
    Serial.println("This is GREEN");
    delay(100);
    
  }
}

void yellowLEDControllerTask(void *pvParameters)
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
    Serial.println("This is YELLOW");
    delay(100);
  }
}

void whiteLEDControllerTask(void *pvParameters)
{
  pinMode(WHITE,OUTPUT);
  while(1)
  {
    Serial.println("This is WHITE");
    delay(100);
  }
}

void loop()
{
}
