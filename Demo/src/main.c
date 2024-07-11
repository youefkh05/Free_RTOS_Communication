#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h> // Include the header file for boolean type
#include <stdlib.h>
#include "diag/trace.h"


/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"


#define CCM_RAM __attribute__((section(".ccmram")))


// ----------------------------------------------------------------------------

/* LED
#include "led.h"

#define BLINK_PORT_NUMBER         (3)
#define BLINK_PIN_NUMBER_GREEN    (12)
#define BLINK_PIN_NUMBER_ORANGE   (13)
#define BLINK_PIN_NUMBER_RED      (14)
#define BLINK_PIN_NUMBER_BLUE     (15)
#define BLINK_ACTIVE_LOW          (false)

struct led blinkLeds[4];
*/

/* functions definitions */
//static void prvOneShotTimerCallback( TimerHandle_t xTimer );
static void prvAutoReloadTimerCallback( TimerHandle_t xTimer );
static int uniform_distribution(int rangeLow, int rangeHigh);
static unsigned int arraytotal(unsigned int arr[],int n);
static void statistics(int taskID);
static FILE * createCVS(void);
static void writeCVS(FILE * Fp);
static void reset(void);
static void endProgram(void);


/* specifications definitions */
#define queue_size 				 3
#define max_message_size		 50
#define receiver_sleep 			 100
#define receiver_max_message	 10
#define receiver_piority 		 3
#define stack_max_size 			 1024
#define sender_low_piority		 1
#define sender_high_piority		 2
#define senders_num				 3
const int lower[] = {50, 80, 110, 140, 170, 200};
const int upper[] = {150, 200, 250, 300,350, 400};

// Define separate counters for each sender task
unsigned int transmit[senders_num]={0};
unsigned int block[senders_num]={0};
unsigned int totalrandom[senders_num]={0};
unsigned int randomnum[senders_num]={0};
unsigned int received=0;
unsigned int receivedblocked=0;
unsigned int iteration=0;

// Declare global task handles
TaskHandle_t TaskHandle_Sender1low, TaskHandle_Sender2low, TaskHandle_Senderhigh;
TimerHandle_t xSenderTimers[senders_num];
TimerHandle_t xReceiverTimer;
QueueHandle_t Queue_Handler = 0; //globalQueue
SemaphoreHandle_t senderSemaphore[senders_num];
SemaphoreHandle_t receiverSemaphore;

//CVS file
FILE *FCVS=NULL;


static void SenderTask( void ){
	//the sender variables
	BaseType_t xStatus;
	int taskindex=0;
	char message[max_message_size];

	//getting the task index
	if (xTaskGetCurrentTaskHandle()  == TaskHandle_Sender1low) {
		taskindex=0;
	} else if (xTaskGetCurrentTaskHandle()  == TaskHandle_Sender2low) {
		taskindex=1;
	} else if (xTaskGetCurrentTaskHandle() == TaskHandle_Senderhigh) {
		taskindex=2;
	}

	/* As per most tasks, this task is implemented within an infinite loop. */
	while(1){

		// Prepare the message with current system ticks
		snprintf(message, sizeof(message), "Time is %lu", xTaskGetTickCount());
		xStatus=!pdPASS;

		//check the semaphore
		if (xSemaphoreTake(senderSemaphore[taskindex], 25) == pdTRUE){
			//Send to queue
			xStatus = xQueueSend(Queue_Handler, &message, 1);

			// Update the appropriate counter
			if ( xStatus != pdPASS ) { //failed from queue
				 block[taskindex]++;
				 //trace_printf("sent %d blocked from queue : %d\n",taskindex+1, block[taskindex]);
			}
			else{
				transmit[taskindex]++;
				// Read the period of the timer
				unsigned int timerPeriod = xTimerGetPeriod(xSenderTimers[taskindex]);
				timerPeriod=timerPeriod * portTICK_PERIOD_MS;

				//add it to the sum
			    totalrandom[taskindex]=totalrandom[taskindex]+timerPeriod;
			    randomnum[taskindex]++;

			    //change the period
			    xTimerChangePeriod(xSenderTimers[taskindex], uniform_distribution(lower[iteration], upper[iteration]), 1);
			    trace_printf("at time period %d :\n sent %d number %d message: %s \n",timerPeriod,taskindex+1, transmit[taskindex],message);
			}
		}
		else{	//blocked from semaphore
			//trace_printf("sent %d blocked from semaphore : %d\n",taskindex+1, block[taskindex]);
		 }
	}
}

static void ReceiverTask( void ){
	//to receive the message
	char receivedMessage[max_message_size];
	BaseType_t status;

	//infinte loop
	while(1){
		//check the semaphore
		if(xSemaphoreTake(receiverSemaphore, 25) == pdTRUE){
			//checkqueue
			status = xQueueReceive(Queue_Handler, &receivedMessage, 0);

			if( status == pdPASS ){ //received
				received++;
				//trace_printf("Received %d:\n %s\n",received, receivedMessage);

				//check if it reached max
				if(received>=receiver_max_message){
					//print the statistics
					trace_printf("Itteration %d:\n",iteration+1);
					trace_printf("Time boundary %d - %d:\n",lower[iteration],upper[iteration]);
					for(int i=0;i<senders_num+1;i++)
						statistics(i);
					writeCVS(FCVS);
					reset();
					iteration++;

					//check if it's the last iteration
					if (iteration >= sizeof(lower) / sizeof(lower[0])) {
						endProgram();
					}
				}
			}
			else { //failed from queue
				receivedblocked++;
				//trace_printf( "Could not receive from the queue %d \nBut received is %d\n",receivedblocked,received);
			}
		}
		else { //blocked from semaphore
			//trace_printf( "Semaphore blocked receiver %d\nBut received is %d\n",receivedblocked,received);
		}
	}
}

int main()
{
	//start random
	srand(time(NULL));

	//create cvs file
	FCVS=createCVS();
	//fclose(FCVS);

	Queue_Handler=xQueueCreate(queue_size,sizeof(char*));	//creating the queue

	/* creating the tasks */
	xTaskCreate(SenderTask,(signed char*) "Sender1low", stack_max_size, NULL,sender_low_piority, &TaskHandle_Sender1low);
	xTaskCreate(SenderTask,(signed char*) "Sender2low", stack_max_size, NULL,sender_low_piority, &TaskHandle_Sender2low);
	xTaskCreate(SenderTask,(signed char*) "Senderhigh", stack_max_size, NULL,sender_high_piority, &TaskHandle_Senderhigh);
	xTaskCreate(ReceiverTask,(signed char*) "ReceiverTask", stack_max_size, NULL,receiver_piority, NULL);

	/* creating the timers */
	xReceiverTimer = xTimerCreate("ReceiverTimer",receiver_sleep , pdTRUE, (void *)3, prvAutoReloadTimerCallback);

	xSenderTimers[0] = xTimerCreate("Sender1Timer", uniform_distribution(lower[iteration], upper[iteration]), pdTRUE, (void *)0, prvAutoReloadTimerCallback);
	xSenderTimers[1] = xTimerCreate("Sender2Timer", uniform_distribution(lower[iteration], upper[iteration]), pdTRUE, (void *)1, prvAutoReloadTimerCallback);
	xSenderTimers[2] = xTimerCreate("Sender3Timer", uniform_distribution(lower[iteration], upper[iteration]), pdTRUE, (void *)2, prvAutoReloadTimerCallback);
	bool initial_test=true;

	//checking the timers
	for(int i=0;i<senders_num || initial_test==false;i++){
		if(xSenderTimers[i]==NULL){
			trace_printf("send timer %d isn't created\n",i);
			initial_test=false;
		}
	}

	if(xReceiverTimer==NULL){
		trace_printf("R timer isn't created\n");
		initial_test=false;
	}

	//start the timers
	if(initial_test)
	{
		for(int i=0;i<senders_num || initial_test==false;i++){
			if(xTimerStart(xSenderTimers[i], 0)!=pdPASS){
				trace_printf("send timer%d didn't start\n",i);
				initial_test=false;
			}
		}
	}

	//check if timers started
	if(xTimerStart(xReceiverTimer, 0)!=pdPASS){
		trace_printf("R timer didn't start\n");
		initial_test=false;
	}

	//creating the semaphore
	for (int i = 0; i < senders_num; i++) {
	    senderSemaphore[i] = xSemaphoreCreateBinary();
	    if (senderSemaphore[i] == NULL) {
	        trace_printf("Failed to create semaphore %d\n", i);
	        initial_test=false;
	    }
	}

	 receiverSemaphore = xSemaphoreCreateBinary();
	 if (receiverSemaphore == NULL) {
		 trace_printf("Failed to create R semaphore \n");
		 initial_test=false;
	 }

	//check if everything is ok
	if(initial_test)
	{
		trace_printf("Program Could Start\n");
		vTaskStartScheduler();
	}


	trace_printf("Program Couldn't Start\n");
	return 0;
}


// ----------------------------------------------------------------------------
/*
static void prvOneShotTimerCallback( TimerHandle_t xTimer )
{
	trace_puts("One-shot timer callback executing");
	turn_on (&blinkLeds[1]);
}
*/

static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
{
	// Retrieve the timer ID
	uint32_t timerID = (uint32_t)pvTimerGetTimerID(xTimer);
	//trace_printf("Auto-Reload timer callback executing %d\n",timerID+1);

	//give the R semaphore
	if(timerID>=senders_num){
		//give the semaphore
		xSemaphoreGive(receiverSemaphore);
		return;
	}

	/*
	if(isOn(blinkLeds[0])){
		turn_off(&blinkLeds[0]);
	} else {
		turn_on(&blinkLeds[0]);
	}
	*/

	//give the semaphore
	xSemaphoreGive(senderSemaphore[timerID]);
}

static int uniform_distribution(int rangeLow, int rangeHigh) {

    double myRand = rand()/(1.0 + RAND_MAX);
    int range = rangeHigh - rangeLow + 1;
    int myRand_scaled = (myRand * range) + rangeLow;
    //trace_printf("Random value is %d\n",myRand_scaled);
    return myRand_scaled;
}

static void statistics(int taskID){

	if(taskID>=senders_num){
		trace_printf("Receiver statistics:\n");
		trace_printf("Received : %d\n", received);
		trace_printf("blocked : %d\n", receivedblocked);
		trace_printf("Total Random : %d\n",arraytotal(totalrandom,sizeof(totalrandom)/sizeof(totalrandom[0])));
		trace_printf("Random num : %d\n",arraytotal(randomnum,sizeof(randomnum)/sizeof(randomnum[0])));
		//trace_printf("Total Avg : %d",arraytotal(totalrandom,senders_num));
		trace_printf("\n\n\n");
	}
	else{
		trace_printf("task %d statistics:\n", taskID+1);
		trace_printf("sent : %d\n", transmit[taskID]);
		trace_printf("blocked : %d\n", block[taskID]);
		trace_printf("Average Tsend : %d\n",totalrandom[taskID]/randomnum[taskID]);
		trace_printf("\n");
	}
}

static void reset(void){

	//clear the arrays
	for(int i=0;i<senders_num;i++){
		transmit[i]=0;
		block[i]=0;
		totalrandom[i]=0;
		randomnum[i]=0;
	}

	//clear the variables
	received=0;
	receivedblocked=0;

	//clear the queue
	xQueueReset(Queue_Handler);
}

unsigned int arraytotal(unsigned int arr[],int n){
	int total=0;
	for(int i=0;i<n;i++)
		total+=arr[i];
	return total;
}

static void endProgram() {

	//delete the timers
	for(int i=0;i<senders_num;i++){
		xTimerDelete(xSenderTimers[i], 1);
	}
	xTimerDelete(xReceiverTimer, 10);

    // Print the "Game Over" message
	trace_printf("Game Over\n");

	//close CVS
	fclose(FCVS);

	//end the program
    exit(0);
}

static FILE * createCVS(void){
	// Open the CSV file in write mode
	FILE *Fp = fopen("statisticst.csv", "w");
	if (Fp == NULL) {
		trace_printf("Failed to open statistics.csv for writing\n");
		return Fp;
	}
	fprintf(Fp," iteration ,");

	//senders
	for(int i=1;i<=senders_num;i++){
		fprintf(Fp," task%d sent , task%d blocked , Tsend%d avg",i,i,i);
	}

	//receiver
	fprintf(Fp," Received , R blocked ,");

	//total
	fprintf(Fp," Total random , Random num , Total avg ,");

	//boundaries
	fprintf(Fp," Lower bound , Upper bound\n");

	trace_printf("CVS created\n");
	return Fp;
}

static void writeCVS(FILE * Fp){

	//check the file
	if(Fp==NULL){
		printf("couldn't write CVS\n");
		return;
	}

	fprintf(Fp," %d ,",iteration+1);

	//senders
	for(int i=0;i<senders_num;i++){
		fprintf(Fp," %d , %d  , %d ,",transmit[i],block[i],totalrandom[i]/randomnum[i]);
	}

	//total
	fprintf(Fp," %d ,",arraytotal(totalrandom,sizeof(totalrandom)/sizeof(totalrandom[0])));
	fprintf(Fp," %d ,",arraytotal(randomnum,sizeof(randomnum)/sizeof(randomnum[0])));
	fprintf(Fp," %d ,",arraytotal(totalrandom,sizeof(totalrandom)/sizeof(totalrandom[0]))/senders_num);

	//boundaries
	fprintf(Fp," %d , %d \n",lower[iteration],upper[iteration]);

}


void vApplicationMallocFailedHook(void) {
    for (;;);
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
    (void)pcTaskName;
    (void)pxTask;
    for (;;);
}

void vApplicationIdleHook(void) {
    volatile size_t xFreeStackSpace;
    xFreeStackSpace = xPortGetFreeHeapSize();

    if (xFreeStackSpace > 100) {
        // Adjust the value of configTOTAL_HEAP_SIZE if necessary.
    }
}

void vApplicationTickHook(void) {
}

StaticTask_t xIdleTaskTCB CCM_RAM;
StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE] CCM_RAM;

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

StaticTask_t xTimerTaskTCB CCM_RAM;
StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH] CCM_RAM;

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize) {
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
