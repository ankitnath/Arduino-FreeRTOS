#include<Arduino_FreeRTOS.h>

#define GREEN 7
#define YELLOW 6
#define WHITE 5

typedef int TaskProfiler;

TaskProfiler GreenLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler WhiteLEDProfiler;

const uint16_t *WhiteLED = (uint16_t *) WHITE; // its a pointer of constant type pointing towards the address of the White LED
const uint16_t *YellowLED = (uint16_t *) YELLOW; 
const uint16_t *GreenLED = (uint16_t *) GREEN;

void setup()
{
  xTaskCreate(ledControlTask,"Green LED Task",100,(void *)GreenLED ,1,NULL);
  xTaskCreate(ledControlTask,"Yellow LED Task",100,(void *)YellowLED ,1,NULL);
  xTaskCreate(ledControlTask,"White LED Task",100,(void *)WhiteLED ,1,NULL);
  
}

void ledControlTask(void *pvParameters)
{
  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(WHITE,OUTPUT);

  while(1)
  {
    digitalWrite(pvParameters,digitalRead(pvParameters)^1);
  }
}

void loop()
{
  
}
