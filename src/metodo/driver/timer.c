#include <driver/driver.h>
#include <driver/timer.h>

unsigned int ticks = 0;

void HalTimerHandler(UNUSED struct regs *r)
{
	//Increment ticks
	ticks++;

  // Put any handlers here.
}

unsigned int HalGetTicks()
{
	return ticks;
}

void HalTimerInit()
{
	HalIrqHandler_Install(0, (void*)HalTimerHandler);
}
