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
  Serial.begin(9600);
  xTaskCreate(greenLedControllerTask, "Green Led Task",100,NULL,1,&green_Handle);
  xTaskCreate(yellowLedControllerTask, "Yellow Led Task",100,NULL,1,&yellow_Handle);
  xTaskCreate(redLedControllerTask, "Red Led Task",100,NULL,1,&red_Handle);
  
 }

void greenLedControllerTask(void *pvParameters)
{ 
  pinMode(GREEN,OUTPUT);
  while(1)
  {  GreenLedProfiler++;
     Serial.print("Green LED run time : ");
    Serial.println(GreenLedProfiler);
    digitalWrite(GREEN,digitalRead(GREEN)^1);
    vTaskDelay(200/portTICK_PERIOD_MS);
//    vTaskDelay(1000);
//   delay(300);
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
    YellowLedProfiler++;
    Serial.print("Yellow LED run time : ");
    Serial.println(YellowLedProfiler);
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    vTaskDelay(300/portTICK_PERIOD_MS);
   //vTaskDelay(1000);
//   delay(300);
  }
}

void redLedControllerTask(void *pvParameters)
{
  RedLedProfiler++;
  pinMode(RED,OUTPUT);
  while(1)
  {
    RedLedProfiler++;
  digitalWrite(RED,digitalRead(RED)^1);
  Serial.print("RedTask run time : ");
  Serial.println(RedLedProfiler);
   vTaskPrioritySet(NULL,2);
   vTaskDelay(500/portTICK_PERIOD_MS);
  //   vTaskDelay(1000);
//   delay(300);
  }
}

void loop()
{
}
