#include <allocation.h>

////////////////////////////////////////////////////////////////////////////////
/// PUBLIC FUNCTION
////////////////////////////////////////////////////////////////////////////////

void print_ptr(unsigned long long ptr)
{
	const char hex[16] = "0123456789abcdef";
	char s[16];
	int i;

	i = 0;
	if (ptr == 0)
		s[i++] = '0';
	while (ptr != 0)
	{
		s[i++] = hex[ptr % 16];
		ptr /= 16;
	}
	write(1, "0x", 2);
	while (i--)
		write(1, (const void *)&(s[i]), 1);
}

void print_str(char *str)
{
	if (str == NULL)
		return;

	while (*str)
	{
		write(1, (const void *)&(*str), 1);
		str += 1;
	}
}

void *_memcpy(void *dst, const void *src, size_t n)
{
	size_t index;
	char *dest;

	index = 0;
	if (src == NULL)
		return ((void *)dst);

	dest = (char *)dst;

	while (index < n)
	{
		dest[index] = ((char *)src)[index];
		index += 1;
	}

	return ((void *)dest);
}

void _bzero(void *s, size_t n)
{
	char *dest;
	size_t index;

	if (s == NULL)
		return;

	dest = (char *)s;
	index = 0;

	while (index < n)
	{
		dest[index] = 0;
		index += 1;
	}
}

void print_num(size_t num)
{
	char c;

	if (num > 9)
	{
		print_num(num / 10);
		print_num(num % 10);
	}
	else
	{
		c = num + '0';
		write(1, (const void *)&c, 1);
	}
}