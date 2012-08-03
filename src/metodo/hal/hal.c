#include <metodo/metodo.h>
#include <string.h>

#include <driver/uart.h>

void StartService(const char *msg, const char *name, void (*func)())
{
	size_t i;
	printf("%s %s", msg, name);
	for(i = 0; i < (50 - strlen(msg) - strlen(name)); i++)
		printf(" ");
	printf(" [BUSY]");
	//printf("%s %s\n\b\b\b\b\b\b\b[BUSY]", msg, name);
	func();
	printf("\b\b\b\b\bDONE]\n");
}

void StartInitializer(const char *name, void (*func)())
{
	StartService("Initializing", name, func);
}

void HalInit(void) {
	HalInitGDT();
	DisplayInit();
	printf(DUX_FULLNAME "\nCompiled at " __TIME__ " " __DATE__ "\n\n\n");

	StartInitializer("IDT", &HalInitIDT);
	StartInitializer("ISRs", &HalIsrInstall);
	StartInitializer("IRQs", &HalIrqInstall);
	StartInitializer("system timer", &HalTimerInit);
	StartInitializer("memory management", &init_mm);
	StartInitializer("keyboard", &HalKeyboardInit);

	StartService("Enabling", "interrupts", &HalEnableInterrupts);
}
