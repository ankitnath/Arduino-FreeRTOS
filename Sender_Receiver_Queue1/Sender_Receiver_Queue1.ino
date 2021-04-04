#include <Arduino_FreeRTOS.h>
#include <queue.h>
QueueHandle_t xQueue;
void setup() 
{
  Serial.begin(9600);
  xQueue = xQueueCreate( 5, sizeof( long ) );
  //xQueueCreate() allocates memory according to data size and queue length
  
if( xQueue != NULL ) //xQueue provides reference of the queue to which we want to
//

{
  xTaskCreate( vSenderTask, "Sender1", 240,( void * ) 100, 2, NULL );
  xTaskCreate( vReceiver1, "Receiver1", 240, NULL, 1, NULL );
  xTaskCreate( vReceiver2, "Receiver2", 240, NULL, 3, NULL );
  xTaskCreate( vReceiver3, "Receiver3", 240, NULL, 0, NULL );
  
  vTaskStartScheduler();
}
else
{
/* The queue could not be created. */
}

}

void loop()
{
  // put your main code here, to run repeatedly:

}

void vSenderTask( void *pvParameters )
{
long lValueToSend;

lValueToSend = ( long ) pvParameters;
  for( ;; )
  {
  xQueueSend( xQueue, &lValueToSend, portMAX_DELAY );
  Serial.println("Sender task activated");
  Serial.print( "Sent = ");
  Serial.println(lValueToSend);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  taskYIELD();
  }
}


void vReceiver1( void *pvParameters )
{
long lReceivedValue;
  for( ;; )
  {
  
    if (xQueueReceive( xQueue, &lReceivedValue, portMAX_DELAY ) == pdPASS)
    {
    Serial.println(" Receiver 1 ");
    Serial.print( "Received = ");
    Serial.println(lReceivedValue);
    Serial.println("Task 1 completed");
    vTaskDelay(500/portTICK_PERIOD_MS);
    }
    taskYIELD();  
  }
}

void vReceiver2( void *pvParameters )
{
long lReceivedValue;
  for( ;; )
  {
  
    if (xQueueReceive( xQueue, &lReceivedValue, portMAX_DELAY ) == pdPASS)
    {
    Serial.println(" Receiver 2 ");
    Serial.print( "Received = ");
    Serial.println(lReceivedValue);
    Serial.println("Task 2 completed");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    taskYIELD();  
  }
}

void vReceiver3( void *pvParameters )
{
long lReceivedValue;
  for( ;; )
  {
  
    if (xQueueReceive( xQueue, &lReceivedValue, portMAX_DELAY ) == pdPASS)
    {
    Serial.println(" Receiver 3 ");
    Serial.print( "Received = ");
    Serial.println(lReceivedValue);
    Serial.println("Task 3 completed");
    vTaskDelay(100/portTICK_PERIOD_MS);
    }
    taskYIELD();  
  }
}
