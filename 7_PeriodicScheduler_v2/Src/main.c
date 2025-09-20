#include "led.h"
#include "uart.h"

#include "osKernel.h"

#define		QUANTA		10

typedef uint32_t TaskProfiler;
TaskProfiler Task0_Profiler,Task1_Profiler,Task2_Profiler,pTask1_Profiler,pTask2_Profiler;

void motor_run(void);
void motor_stop(void);
void valve_open(void);
void valve_close(void);

void task0(void)
{
	while(1)
	{
		Task0_Profiler++;
		// This task is behaving cooperatively. Once it completes it is giving another thread priority to execute, instead of running for the complete time quanta
		osThreadYield();
	}
}

void task1(void)
{
	while(1)
	{
		Task1_Profiler++;
	}
}

void task2(void)
{
	while(1)
	{
		Task2_Profiler++;
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
	printf("M");
}

void motor_stop(void)
{
	printf("S");
}

void valve_open(void)
{
	printf("V");
}

void valve_close(void)
{
	printf("C");
}


