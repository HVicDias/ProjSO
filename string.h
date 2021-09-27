#ifndef STRING_H
#define STRING_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int strcmp(const char *a, const char *b)
{	
    while (*a && *a == *b) { ++a; ++b; }
    return (int)(unsigned char)(*a) - (int)(unsigned char)(*b);
}

#endif