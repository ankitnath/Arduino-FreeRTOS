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

void setup()
{
   Serial.begin(9600);
   //create structure queue
   Queue1 = xQueueCreate(10,//queue length
                              sizeof(msg1)//Queue item size
                              );
   Queue2 = xQueueCreate(10,//queue length
                              sizeof(msg1)//Queue item size
                              );
   Queue3 = xQueueCreate(10,//queue length
                              sizeof(msg1)//Queue item size
                              );
   if(Queue1 == NULL)
   {
     Serial.println("Error creating queue1");
   }
   else if(Queue2 == NULL)
   {
    Serial.println("Error creating queue2");
   }
   else if(Queue3 == NULL)
   {
    Serial.println("Error creating queue3");
   }


   //Create task that consumers if it is created
     xTaskCreate(ProducerTask, //Task producer
                 "Producer", //Task Name
                  128, //stack size
                  NULL,
                  3, //Priority with 3 being highest, and 0 lowest
                  NULL);

    //Consumers tasks
    xTaskCreate(TaskClient1, //Task function
                "Client1", //Task Name
                128, //stack size
                NULL,
                2,
                NULL);

    xTaskCreate(TaskClient2, //Task function
                "Client2", //Task Name
                128, //stack size
                NULL,
                1,
                NULL);

    xTaskCreate(TaskClient3, //Task function
                "Client3", //Task Name
                128, //stack size
                NULL,
                3,  //highest priority
                NULL);

vTaskStartScheduler();
}

void loop()
{
}

//client1

void TaskClient1(void *pvParameters)
{
  (void) pvParameters;
  vTaskDelay(2);
  for(;;)
  {
    
    if(xQueueReceive(Queue1,&msg1, portMAX_DELAY) == pdPASS)
     {
       //print received data elements on serial monitor
       Serial.println("  client1 started  ");
       Serial.println(msg1);

       //condition check to see if data receive from channel zero
       // if yes store value member of structure in temp variable
       if(msg1=="3")
       {
         Serial.println("ServerES produced Unit2 ");
         vTaskDelay(1000/portTICK_PERIOD_MS);
       }
     }
    taskYIELD(); //terminate the task and inform scheduler about it 
  }
}

//client2

void TaskClient2(void *pvParameters)
{
  (void) pvParameters;
vTaskDelay(2);
  for(;;)
  {
    
    if(xQueueReceive(Queue2,&msg2, portMAX_DELAY) == pdPASS)
     {
       //print received data elements on serial monitor
       Serial.println("  client2 started  ");
       Serial.println(msg2);

       //condition check to see if data receive from channel zero
       // if yes store value member of structure in temp variable
       if(msg2=="2")
       {
         Serial.println(" ServerES produced Unit3 ");
         vTaskDelay(1000/portTICK_PERIOD_MS);
       }
     }
    taskYIELD(); //terminate the task and inform scheduler about it 
  }
}

//client3

void TaskClient3(void *pvParameters)
{
  vTaskDelay(2);
  (void) pvParameters;

  for(;;)
  {
    
    if(xQueueReceive(Queue3,&msg3, portMAX_DELAY) == pdPASS)
     {
       //print received data elements on serial monitor
       Serial.println("  client3 started  ");
       Serial.println(msg3);
    
       //condition check to see if data receive from channel zero
       // if yes store value member of structure in temp variable
       if(msg1=="1")
       {
         Serial.println("  Client3 is receiving  ");
         vTaskDelay(1000/portTICK_PERIOD_MS);
       }
     }
    taskYIELD(); //terminate the task and inform scheduler about it 
  }
}

//Producer 
void ProducerTask(void *pvParameters)
{
  vTaskDelay(2);
  (void) pvParameters;

  for(;;)
  {
     
     msg1 = "1";
     msg2 = "2";
     msg3 = "3";

     Serial.println("ServerEs started");
     xQueueSend(Queue1,&msg1,portMAX_DELAY); //write struct message in queue
     Serial.println("Unit 2 produced ");
     vTaskDelay(1000/portTICK_PERIOD_MS);
     
     xQueueSend(Queue2,&msg2,portMAX_DELAY); //write struct message in queue
     Serial.println("Unit 3 produced ");
     vTaskDelay(1000/portTICK_PERIOD_MS);

     xQueueSend(Queue3,&msg3,portMAX_DELAY); //write struct message in queue
     Serial.println("Unit 1 produced ");
     vTaskDelay(1000/portTICK_PERIOD_MS);
 //    taskYIELD();
  }
}
