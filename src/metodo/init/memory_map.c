#include <metodo/metodo.h>
#include <metodo/init/memory_map.h>

void MMapSetup(void *arg)
{
	int i;
	memory_map_t *mmap;
	memory_map_t *first_empty_mmap;
	switch(bootloader) {
		case BOOTLOADER_MULTIBOOT:
			mmap = (memory_map_t*)mbd->mmap_addr;
			first_empty_mmap = (memory_map_t*)(mbd->mmap_addr + mbd->mmap_length);
			break;
		case BOOTLOADER_BEEF:
			mmap = (memory_map_t*)arg;
			// How would I define first_empty_mmap here?
			break;
	}

	for (i = 0; mmap < first_empty_mmap; i++, mmap++)
		mmaps[i] = mmap;
	for (i++, mmap++; i < 100; i++, mmap++)
		mmaps[i] = NULL;
}

void MMapPrint() {
	int i;
	printf("Memory map:\n");
	printf("\
          |      base addr      |       length\n\
   size   |   low    |   high   |   low    |   high   |   type\n");
	for (i = 0; mmaps[i] != NULL; i++) {
		printf(" %8x | %8x | %8x | %8x | %8x | %8x\n",
		mmaps[i]->size, mmaps[i]->base_addr_low, mmaps[i]->base_addr_high,
		mmaps[i]->length_low, mmaps[i]->length_high, mmaps[i]->type);
	}
}
