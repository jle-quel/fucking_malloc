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

#define TINY 1
#define SMALL 2
#define LARGE 4

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
void *new_page(uint8_t const allocation_type, size_t const size);
void *search_page(uint8_t const allocation_type, size_t const size);

/// FREE

void free(void *ptr);

/// REALLOC

void *realloc(void *ptr, size_t size);

/// CALLOC

void *calloc(size_t count, size_t eltsize);

/// SHOW_ALLOC_MEM

void show_alloc_mem(void);

/// UTILS

t_header **arena(void);
void create_meta(uint8_t const status, size_t const size, void *ptr, void *next);
void create_header(uint8_t const allocation_type, size_t const page_size, void *ptr);

/// LIB

void print_num(size_t num);
void _bzero(void *s, size_t n);
void *_memcpy(void *dst, const void *src, size_t n);
void print_str(char *str);
void print_ptr(unsigned long long ptr);

#endif
