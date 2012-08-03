#include <metodo/init/init.h>

noreturn InitKernel(uint32_t magic, void *arg)
{
	void *userland = NULL;

	InitDetectBootloader(magic, arg); // Detect bootloader
	MMapSetup(arg);    // Set up memory map first
	HalInit();         // Start HAL (GDT, Display, IDT, etc)

	InitLoadModules(); // Load all kernel modules

	printf("Kernel size is approximately %i bytes (start: 0x%08x, end: 0x%08x)\n", &end-&start, &start, &end);

	HalBreak();
}
