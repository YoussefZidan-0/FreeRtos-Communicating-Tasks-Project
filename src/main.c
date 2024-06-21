#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"
#include <stdint.h>
#include <limits.h>
#include "led.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#define CSV_FILENAME "freertos_log.csv"

// CSV header format
#define CSV_HEADER "Iteration,Total_Successful_Messages,Total_Blocked_Messages,Sent1,Blocked1,Sent2,Blocked2,Sent3,Blocked3,Avg_Tsender,Tsender1,Tsender2,Tsender3\n"

FILE *csv_file;
#include <time.h>   // Include for time operations

#define CCM_RAM __attribute__((section(".ccmram")))
#define FIXED_Receiver_Time pdMS_TO_TICKS(100)

// LED-related definitions
#define BLINK_PORT_NUMBER         (3)
#define BLINK_PIN_NUMBER_GREEN    (12)
#define BLINK_PIN_NUMBER_ORANGE   (13)
#define BLINK_PIN_NUMBER_RED      (14)
#define BLINK_PIN_NUMBER_BLUE     (15)
#define BLINK_ACTIVE_LOW          (false)
#define Queue_Size   				10

struct led blinkLeds[4];

static void prvOneShotTimerCallback(TimerHandle_t xTimer);
static void prvAutoReloadTimerCallback(TimerHandle_t xTimer);
static void vSender1TimerCallback(TimerHandle_t xTimer);
static void vSender2TimerCallback(TimerHandle_t xTimer);
static void vSender3TimerCallback(TimerHandle_t xTimer);
static void vReceiverTimerCallback(TimerHandle_t xTimer);
// Timer handles
static TimerHandle_t xTimerOneShot = NULL;
static TimerHandle_t xTimerAutoReload = NULL;
static TimerHandle_t xTimer1;
static TimerHandle_t xTimer2;
static TimerHandle_t xTimer3;
static TimerHandle_t xTimer4;
int Tsender1, Tsender2, Tsender3;
double tot3,tot2,tot1 =0;
BaseType_t xTimer1Started, xTimer2Started;

// Task and Queue handles
QueueHandle_t xQueue;
SemaphoreHandle_t xSemaphoreSender1, xSemaphoreSender2, xSemaphoreSender3, xSemaphoreReceiver;
TickType_t Treceiver = pdMS_TO_TICKS(100);
TickType_t lower_arr[6] = {50, 80, 110, 140, 170, 200};
TickType_t upper_arr[6] = {150, 200, 250, 300, 350, 400};
int sent1, sent2, sent3, block1, block2, block3;
int received_message, total_number_of_blocked_messages, total_number_of_successfully_sent_messages, upper, lower;
int iteration = -1;
int callback1, callback2, callback3;

// Uniform distribution function
int uniform_dist() {
    return (rand() % (upper - lower + 1)) + lower;
}

// Sender task functions
static void Sender1(void *parameters) {
    char ivaluetosend[50];
    BaseType_t xStatus;

    while (1) {
        xSemaphoreTake(xSemaphoreSender1, portMAX_DELAY);
        snprintf(ivaluetosend, sizeof(ivaluetosend), "Time is %lu", xTaskGetTickCount());
        xStatus = xQueueSend(xQueue, ivaluetosend, 0);
      //  trace_printf("Tsender1 :...%d\n",Tsender1);

        if (xStatus == pdPASS) {
            sent1++;
        } else {
            block1++;
        }
       // Tsender1=uniform_dist();
        	callback1++;
          tot1=tot1+Tsender1;
          xTimerChangePeriod(xTimer1, pdMS_TO_TICKS(Tsender1), 0);
          Tsender1=uniform_dist();

       // xTimerStart(xTimer1, 0);
    }
}

static void Sender2(void *parameters) {
    char ivaluetosend[50];
    BaseType_t xStatus;

    while (1) {
        xSemaphoreTake(xSemaphoreSender2, portMAX_DELAY);
        snprintf(ivaluetosend, sizeof(ivaluetosend), "Time is %lu", xTaskGetTickCount());
        xStatus = xQueueSend(xQueue, ivaluetosend, 0);
   //     trace_printf("Tsender2 :...%d\n",Tsender2);

        if (xStatus == pdPASS) {
            sent2++;
        } else {
            block2++;
        }
       // Tsender2=uniform_dist();
        	callback2++;
          tot2=tot2+Tsender2;
          xTimerChangePeriod(xTimer2, pdMS_TO_TICKS(Tsender2), 0);
          Tsender2=uniform_dist();

       // xTimerStart(xTimer2, 0);
    }
}

static void Sender3(void *parameters) {
    char ivaluetosend[50];
    BaseType_t xStatus;

    while (1) {
     //   trace_printf("Sender3: Waiting for semaphore...\n");
        xSemaphoreTake(xSemaphoreSender3, portMAX_DELAY);
     //   trace_printf("Sender3: Semaphore taken\n");
       // trace_printf("Tsender3 :...%d\n",Tsender3);
        snprintf(ivaluetosend, sizeof(ivaluetosend), "Time is %lu", xTaskGetTickCount());
        xStatus = xQueueSend(xQueue, ivaluetosend, 0);

        if (xStatus == pdPASS) {
      //      trace_printf("Sender3: Message sent successfully\n");
            sent3++;
        } else {
          //  trace_printf("Sender3: Failed to send message (queue full)\n");
            block3++;
        }
     //   Tsender3=uniform_dist();
        callback3++;
        tot3=tot3+Tsender3;
        xTimerChangePeriod(xTimer3, pdMS_TO_TICKS(Tsender3), 0);
        Tsender3=uniform_dist();

     //   xTimerStart(xTimer3, 0);
    }
}

// Receiver task function
static void Receiver(void *parameters) {
    char receivedValue[50];
    BaseType_t xStatus;

    while (1) {
        // Wait for the semaphore to be given by the timer callback
        xSemaphoreTake(xSemaphoreReceiver, portMAX_DELAY);
        // Attempt to read from the queue, wait up to Treceiver ticks if necessary
        xStatus = xQueueReceive(xQueue, &receivedValue, Treceiver);

        if (xStatus == pdPASS) {
            received_message++;
            printf("Received message: %s\n", receivedValue);
        }

        // Check if 1000 messages have been received
        if (received_message >= 1000) {
            Reset();
        }

        // Restart the receiver timer
       //  xTimerStart(xTimer4, 0);
    }
}

// Timer callback functions
void vSender1TimerCallback(TimerHandle_t xTimer) {
    xSemaphoreGive(xSemaphoreSender1);

}

void vSender2TimerCallback(TimerHandle_t xTimer) {
    xSemaphoreGive(xSemaphoreSender2);

}

void vSender3TimerCallback(TimerHandle_t xTimer) {
  //  trace_printf("I'm callback 3\n");
    xSemaphoreGive(xSemaphoreSender3);


}

void vReceiverTimerCallback(TimerHandle_t xTimer) {
   // trace_printf("I'm callback Receiver\n");
    xSemaphoreGive(xSemaphoreReceiver);
}

// Reset function
void Reset() {
    if (iteration == -1) { // Initial start
        received_message = 0;
        iteration++;
        upper = upper_arr[iteration];
        lower = lower_arr[iteration];
        Tsender1 = uniform_dist();
        Tsender2 = uniform_dist();
        Tsender3 = uniform_dist();

    } else if (iteration <= 5) {
        total_number_of_successfully_sent_messages = sent1 + sent2 + sent3;
        total_number_of_blocked_messages = block1 + block2 + block3;
        	int tavg1=tot1/callback1;
        	int tavg2=tot2/callback2;
        	int tavg3=tot3/callback3;
        	int totavg=(tavg1+tavg2+tavg3)/3;
                sent3+=block3;
                sent2+=block2;
                sent1+=block1;

        printf("Total Successful Messages: %d\n", total_number_of_successfully_sent_messages);
        printf("Total Blocked Messages: %d\n", total_number_of_blocked_messages);
        printf("Statistics for first lower  priority:\n");//first lower
        printf("  Total Successful Messages: %d\n", sent1);
        printf("  Total Blocked Messages: %d\n", block1);
        printf("Statistics for second lower priority:\n");
        printf("  Total Successful Messages: %d\n", sent2);
        printf("  Total Blocked Messages: %d\n", block2);
        printf("Statistics for highest   priority:\n"); //highest
        printf("  Total Successful Messages: %d\n", sent3);
        printf("  Total Blocked Messages: %d\n", block3);
        printf("  Avg Tsender: %d\n", totavg);
        printf("  avgTsender1: %d\n", tavg1);
        printf("  avgTsender2: %d\n", tavg2);
        printf("  avgTsender3: %d\n", tavg3);

        // Write data to CSV file
        fprintf(csv_file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                iteration,
                total_number_of_successfully_sent_messages,
                total_number_of_blocked_messages,
                sent1, block1,
                sent2, block2,
                sent3, block3,
				totavg, tavg1, tavg2, tavg3);

        fflush(csv_file); // Ensure the data is written to the file
        tavg1,tavg2,tavg3,totavg=0;
        iteration++;
        upper = upper_arr[iteration];
        lower = lower_arr[iteration];


    } else {


        printf("Game Over\n");
        fclose(csv_file);
        exit(0);
        vTaskEndScheduler();
        return;
    }

    // Reset counters
    xQueueReset(xQueue);
    total_number_of_successfully_sent_messages = 0;
    total_number_of_blocked_messages = 0;
    received_message = 0;
    sent1 = 0;
    sent2 = 0;
    sent3 = 0;
    block1 = 0;
    block2 = 0;
    block3 = 0;
}

int main() {
    trace_printf("Hello from main\n");
    srand((unsigned int)time(NULL));

    xQueue = xQueueCreate(Queue_Size, sizeof(char[50]));

    if (iteration == -1) {
        Reset();
    }

    xSemaphoreSender1 = xSemaphoreCreateBinary();
    xSemaphoreSender2 = xSemaphoreCreateBinary();
    xSemaphoreSender3 = xSemaphoreCreateBinary();
    xSemaphoreReceiver = xSemaphoreCreateBinary();

    BaseType_t status1 = xTaskCreate(Sender1, "Sender1", 2000, NULL, 1, NULL);
    BaseType_t status2 = xTaskCreate(Sender2, "Sender2", 2000, NULL, 1, NULL);
    BaseType_t status3 = xTaskCreate(Sender3, "Sender3", 2000, NULL, 2, NULL);
    BaseType_t status4 = xTaskCreate(Receiver, "Receiver", 2000, NULL, 3, NULL);

    xTimer1 = xTimerCreate("Tsender1", pdMS_TO_TICKS(Tsender1), pdTRUE, (void *)1, vSender1TimerCallback);
    xTimer2 = xTimerCreate("Tsender2", pdMS_TO_TICKS(Tsender2), pdTRUE, (void *)2, vSender2TimerCallback);
    xTimer3 = xTimerCreate("Tsender3", pdMS_TO_TICKS(Tsender3), pdTRUE, (void *)3, vSender3TimerCallback);
    xTimer4 = xTimerCreate("Treceiver", FIXED_Receiver_Time, pdTRUE, (void *)4, vReceiverTimerCallback);

    xTimerOneShot = xTimerCreate("Timer1", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, prvOneShotTimerCallback);
    xTimerAutoReload = xTimerCreate("Timer2", pdMS_TO_TICKS(1000), pdTRUE, (void *)1, prvAutoReloadTimerCallback);
    BaseType_t startoftimer1 = xTimerStart(xTimer1, 0);
    BaseType_t startoftimer2 = xTimerStart(xTimer2, 0);
    BaseType_t startoftimer3 = xTimerStart(xTimer3, 0);
    BaseType_t startoftimer4 = xTimerStart(xTimer4, 0);

    xTimerStart(xTimerOneShot, 0);
    xTimerStart(xTimerAutoReload, 0);
    // LED setup
    blinkLeds[0] = createLed(BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_GREEN, BLINK_ACTIVE_LOW);
    blinkLeds[1] = createLed(BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_ORANGE, BLINK_ACTIVE_LOW);
    blinkLeds[2] = createLed(BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_RED, BLINK_ACTIVE_LOW);
    blinkLeds[3] = createLed(BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_BLUE, BLINK_ACTIVE_LOW);

    for (int i = 0; i < 4; i++) {
        power_up(&blinkLeds[i]);
    }


    csv_file = fopen(CSV_FILENAME, "w");
    if (csv_file == NULL) {
        printf("Failed to open CSV file for writing.\n");
        return -1;
    }

    // Write CSV header
    fprintf(csv_file, CSV_HEADER);
    fflush(csv_file); // Ensure the header is written to the file

    vTaskStartScheduler();
    trace_printf("Not enough heap memory...\n");

    return 0;
}

#pragma GCC diagnostic pop

// Timer callback implementations
static void prvOneShotTimerCallback(TimerHandle_t xTimer) {
    trace_puts("One-shot timer callback executing");
    turn_on(&blinkLeds[1]);
}

static void prvAutoReloadTimerCallback(TimerHandle_t xTimer) {
    trace_puts("Auto-Reload timer callback executing");

    if (isOn(blinkLeds[0])) {
        turn_off(&blinkLeds[0]);
    } else {
        turn_on(&blinkLeds[0]);
    }
}

// FreeRTOS hook functions
void vApplicationMallocFailedHook(void) {
    for (;;);
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
    (void)pcTaskName;
    (void)pxTask;
    for (;;);
}

void vApplicationIdleHook(void) {
    volatile size_t xFreeStackSpace = xPortGetFreeHeapSize();
    if (xFreeStackSpace > 100) {
        // Adjust heap size if needed
    }
}

void vApplicationTickHook(void) {}

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
