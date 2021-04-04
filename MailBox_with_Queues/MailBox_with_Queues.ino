#include <Arduino_FreeRTOS.h>
#include <queue.h>

QueueHandle_t xMailbox;
TaskHandle_t TaskHandle_1; //handler for task 1
TaskHandle_t TaskHandle_2; //handler for task 2
TaskHandle_t TaskHandle_3; //handler for task 3

void setup()
{
   Serial.begin(9600);
   xMailbox = xQueueCreate(1,sizeof(int32_t));
   Serial.begin(9600);
   xTaskCreate(vUpdateMailbox, "Sender",100,NULL, 1, &TaskHandle_1);
   xTaskCreate(Client1, "Client1",100, NULL, 1, &TaskHandle_2);
   xTaskCreate(Client2, "Client2",100, NULL, 2, &TaskHandle_3);
}

void loop()
{
  
}

void vUpdateMailbox(void)
{
  int32_t ulNewValue = 1;
  while(1)
  {
    xQueueOverwrite(xMailbox, &ulNewValue);
    Serial.println("Data written to mailbox");
    ulNewValue++;
    vTaskDelay(500);
  }
}

BaseType_t Client1(void)
{
  int32_t value_received;
  while(1)
  {
    xQueuePeek(xMailbox, &value_received, portMAX_DELAY);
    Serial.print("Data received by client1 = ");
    Serial.println(value_received);
    vTaskDelay(100);
  }
}

BaseType_t Client2(void)
{
  int32_t value_received;
  while(1)
  {
    xQueuePeek(xMailbox, &value_received, portMAX_DELAY);
    Serial.print("Data received by client2 = ");
    Serial.println(value_received);
    vTaskDelay(100);
  }
}
