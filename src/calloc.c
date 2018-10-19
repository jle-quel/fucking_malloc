#include <allocation.h>

void *calloc(size_t count, size_t eltsize)
{
	size_t size = count * eltsize;
	void *value = malloc(size);
	if (value != 0)
		memset(value, 0, size);
	return value;
}