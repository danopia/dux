#include <metodo.h>

int InitDetectBootloader(uint32_t magic, void *arg)
{
  int bootloader;

	switch(magic) {
		case MULTIBOOT_BOOTLOADER_MAGIC:
			mbd = arg;
			bootloader = BOOTLOADER_MULTIBOOT;
			break;
		default:
			HalInit();
			stop(STOP_BAD_BOOTLOADER_MAGIC);
	}
	return bootloader;
}
