#include <Arduino_FreeRTOS.h>
#include <queue.h>
QueueHandle_t xQueue;
void setup() 
{
    Serial.begin(9600);
    xQueue = xQueueCreate( 5, sizeof( long ) );
    //xQueueCreate(uxQueueLength,uxItemSize) allocates memory according to data size and queue length
    //uxQueueLength --> max number of items that the queue can contain
    //uxItemSize --> The number of bytes each item in the queue will require

    if( xQueue != NULL ) //xQueue provides reference of the queue to which we want to
    {
      xTaskCreate( vSenderTask, "Sender1", 240, ( void * ) 100, 1, NULL );
      xTaskCreate( vSenderTask, "Sender2", 240, ( void * ) 200, 1, NULL );
      xTaskCreate( vReceiverTask, "Receiver", 240, NULL, 2, NULL );
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
  //xQueueSend(QueueHandle_t xQueue, const void * pvItemToQueue, TickType_t xTicksToWait)
  //xQueue --> The handle to the queue on which the item is to be posted
  //pvItemToQueue --> A pointer to the item that is placed on the queue. The size of the items the queue will hold as defined when the queue was created,so this many bytes will be copied from pvItemToQueue into the queue storage area
  //xTicksToWait --> The maximum amount of time the task should block waiting for space to become available on the queue, should it already be full.
  
  Serial.print( "Sent = ");
  Serial.println(lValueToSend);
  taskYIELD();
  }
}
  void vReceiverTask( void *pvParameters )
  {
    long lReceivedValue;
    for( ;; )
    {
    
    if (xQueueReceive( xQueue, &lReceivedValue, portMAX_DELAY ) == pdPASS)
    {
    Serial.print( "Received = ");
    Serial.println(lReceivedValue);
    }
    taskYIELD();
    
   }
  }
