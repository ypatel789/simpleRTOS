#include "led.h"
#include "uart.h"

#include "osKernel.h"

#define		QUANTA		10

typedef uint32_t TaskProfiler;
TaskProfiler Task0_Profiler,Task1_Profiler,Task2_Profiler,pTask1_Profiler,pTask2_Profiler;

int32_t semaphore1, semaphore2;

void motor_run(void);
void motor_stop(void);
void valve_open(void);
void valve_close(void);

void task0(void)
{
	while(1)
	{
		//

	}
}

void task1(void)
{
	while(1)
	{
		osSemaphoreWait(&semaphore1);
		motor_run();
		osSemaphoreSet(&semaphore2);

	}
}

void task2(void)
{
	while(1)
	{
		osSemaphoreWait(&semaphore2);
		valve_open();
		osSemaphoreSet(&semaphore1);

	}
}

void task3(void)
{
	pTask1_Profiler++;
}

int main(void)
{
	// Initialise uart
	uart_tx_init();

	// Initialise hardware timer
	tim2_1hz_interrupt_init();

	// Initialise Semaphores
	osSemaphoreInit(&semaphore1, 1);
	osSemaphoreInit(&semaphore2, 0);

	// Initialise Kernel
	osKernelInit();

	// Add Threads
	osKernelAddThreads(&task0, &task1, &task2);

	// Set RoundRobin time quanta
	osKernelLaunch(QUANTA);
}

void TIM2_IRQHandler(void)
{
	// Clear update interrupt flag
	TIM2->SR &=~SR_UIF;

	// Increment the profiler
	pTask2_Profiler++;
}

void motor_run(void)
{
	printf("Motor is starting...\n\r");
}


void motor_stop(void)
{
	printf("Motor is stopping...\n\r");
}

void valve_open(void)

{
	printf("Valve is opening...\n\r");
}


void valve_close(void)
{
	printf("Valve is closing...\n\r");
}


