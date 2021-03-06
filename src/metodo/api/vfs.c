#include <system.h>
#include <api/vfs.h>

fs_node_t *fs_root = 0;
 
uint32_t FSRead(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
	if(node->read != 0 && node->type != FS_DIRECTORY)
		return node->read(node, offset, size, (char*)buffer);
	else	
		return 0;
}
 
uint32_t FSWrite(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
	if (node->write != 0 && node-> type != FS_DIRECTORY)
		return node->write(node, offset, size, buffer);
	else
		return 0;
}
void FSOpen(fs_node_t *node, uint8_t read, uint8_t write)
{
	if (node->open != 0 && node->type != FS_DIRECTORY)
		return node->open(node, read, write);
	else
		return;
}
 
void FSClose(fs_node_t *node)
{
	if(node->close != 0 && node->type != FS_DIRECTORY)
		return node->close(node);
	else 
		return;
}
 
struct dirent *FSReadDir(fs_node_t *node, uint32_t index)
{
	if(node->readdir != 0) 
        return node->readdir(node, index);
	else
		return NULL;
}
 
fs_node_t *FSFindDir(fs_node_t *node, char *name)
{
	if(node->finddir != 0)
	       return node->finddir(node, name);
	else
		return NULL;	
}
