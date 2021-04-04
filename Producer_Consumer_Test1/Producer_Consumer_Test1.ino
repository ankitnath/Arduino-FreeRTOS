/* code sequence :
 *  --> Client3 created
 *  --> ServerES produces "Unit 1", Client3 receives only receives -- ServerES produced "Unit1"
 *  --> Client1 started
 *  --> ServerES produces "Unit 2", Client1 & Client3 receives -- ServerES produced "Unit2"
 *  --> Client2 started
 *  --> ServerES produces "Unit 3", Client1,Client2 & Client3 receives -- ServerES produced "Unit3"
*/

#include <Arduino_FreeRTOS.h>
#include <queue.h>

String msg1,msg2,msg3;

QueueHandle_t Queue1;
QueueHandle_t Queue2;
QueueHandle_t Queue3;

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;


void setup()
{
   Serial.begin(9600);
   //create structure queue
   Queue1 = xQueueCreate(10,//queue length
                              sizeof(msg1)//Queue item size
                              );
   Queue2 = xQueueCreate(10,//queue length
                              sizeof(msg2)//Queue item size
                              );
   Queue3 = xQueueCreate(10,//queue length
                              sizeof(msg2)//Queue item size
                              );


   //Create producer task
     xTaskCreate(ProducerTask, "Producer", 128, NULL, 2, NULL);

    //Consumer Tasks

    xTaskCreate(TaskClient1, "Client1",128, NULL, 1, &TaskHandle_1);
                
    xTaskCreate(TaskClient2, "Client2", 128, NULL, 1, &TaskHandle_2);

    xTaskCreate(TaskClient3, "Client3", 128, NULL, 3, &TaskHandle_3);
   

vTaskStartScheduler();
}

void loop()
{
}

void TaskClient1(void *pvParameters)
{
  (void) pvParameters;
  for(;;)
   {
  if(xQueueReceive(Queue2,&msg2, portMAX_DELAY) == pdPASS)
  {
    if(msg2=="Unit2")
    {
      Serial.print(msg2);
      Serial.println(" produced");
      Serial.print("Client1 ServerES produced ");
      Serial.println(msg2);
      Serial.print("Client3 ServerES produced ");
      Serial.println(msg2);
      Serial.println("\n");
      vTaskDelay(500/portTICK_PERIOD_MS);   
    }
   }
  }
}

void TaskClient2(void *pvParameters)
{
  (void) pvParameters;
  Serial.println("Client2 started");
  for(;;)
  {
   if(xQueueReceive(Queue3,&msg3, portMAX_DELAY) == pdPASS)
   {
    if(msg3=="Unit3")
    {
      Serial.print(msg3);
      Serial.println(" produced");
      Serial.print("Client1 ServerES produced ");
      Serial.println(msg3);
      Serial.print("Client2 ServerES produced ");
      Serial.println(msg3);
      Serial.print("Client3 ServerES produced ");
      Serial.println(msg3);
      Serial.println("\n");
      vTaskDelay(500/portTICK_PERIOD_MS);      
    }
   }
  } 
}

void TaskClient3(void *pvParameters)
{
  (void) pvParameters;
  Serial.println("Client3 started");
  for(;;)
  {
   if(xQueueReceive(Queue1,&msg1, portMAX_DELAY) == pdPASS)
   {
    if(msg1=="Unit1")
    { 
      Serial.print(msg1);
      Serial.println("  produced");
      Serial.print("Client3 ServerES produced ");
      Serial.println(msg1);
      Serial.println("\n");
      vTaskDelay(500/portTICK_PERIOD_MS);  
      vTaskPrioritySet( TaskHandle_2,2 ); 
    }
   }
  } 
}

//Producer 
void ProducerTask(void *pvParameters)
{
  (void) pvParameters;

  for(;;)
  {
     
     msg1 = "Unit1";
     msg2 = "Unit2";
     msg3 = "Unit3";
     
//     Serial.println("ServerEs started");
     xQueueSend(Queue1,&msg1,portMAX_DELAY); //write struct message in queue
     xQueueSend(Queue2,&msg2,portMAX_DELAY); //write struct message in queue
     xQueueSend(Queue3,&msg3,portMAX_DELAY); //write struct message in queue
     
  }
}
