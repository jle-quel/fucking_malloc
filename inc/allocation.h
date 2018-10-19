#ifndef ALLOCATION_H
#define ALLOCATION_H

////////////////////////////////////////////////////////////////////////////////
/// INCLUDES
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
/// DEFINES
////////////////////////////////////////////////////////////////////////////////

#define FALSE 0
#define TRUE 1
#define MEMORY_ALIGN 16

#define PROT_FLAG PROT_READ | PROT_WRITE
#define MAP_FLAG MAP_ANON | MAP_PRIVATE

#define TINY_MIN 1
#define TINY_MAX 992
#define SMALL_MAX 15359

#define TINY 0x1
#define SMALL 0x2
#define LARGE 0x4

#define TINY_PRE_ALLOC 30 * getpagesize()
#define SMALL_PRE_ALLOC 400 * getpagesize()

////////////////////////////////////////////////////////////////////////////////
/// STRUCTURES
////////////////////////////////////////////////////////////////////////////////

typedef struct s_header
{
	size_t page_size;
	struct s_header *next;
	struct s_meta *opti;
	uint8_t type;
} t_header;

typedef struct s_meta
{
	uint8_t free : 1;
	size_t size : 31;
	struct s_meta *next;
} t_meta;

////////////////////////////////////////////////////////////////////////////////
/// PROTOTYPES
////////////////////////////////////////////////////////////////////////////////

/// MALLOC

void *malloc(size_t size);
void create_meta(const uint8_t status, const size_t size, void *ptr, void *next);
void create_header(const uint8_t allocation_type, const size_t page_size, void *ptr);
t_header **arena(void);
void *new_page(const uint8_t allocation_type, const size_t size);
void *search_page(const uint8_t allocation_type, const size_t size);

/// FREE

void free(void *ptr);

/// REALLOC

void *realloc(void *ptr, size_t size);
void *calloc(size_t count, size_t eltsize);

#endif
