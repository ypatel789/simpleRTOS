#include "led.h"
#include "uart.h"

#include "osKernel.h"

#define		QUANTA		10

typedef uint32_t TaskProfiler;
TaskProfiler Task0_Profiler,Task1_Profiler,Task2_Profiler;

void motor_run(void);
void motor_stop(void);
void valve_open(void);
void valve_close(void);

void task0(void)
{
	while(1)
	{
		Task0_Profiler++;
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

int main(void)
{
	// Initialise Kernel
	osKernelInit();

	// Add Threads
	osKernelAddThreads(&task0, &task1, &task2);

	// Set RoundRobin time quanta
	osKernelLaunch(QUANTA);
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


