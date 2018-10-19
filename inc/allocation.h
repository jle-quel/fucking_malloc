#ifndef ALLOCATION_H
# define ALLOCATION_H

////////////////////////////////////////////////////////////////////////////////
/// INCLUDES 
////////////////////////////////////////////////////////////////////////////////

# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>

////////////////////////////////////////////////////////////////////////////////
/// DEFINES 
////////////////////////////////////////////////////////////////////////////////

# define FALSE 0
# define TRUE 1
# define MEMORY_ALIGN 16

# define PROT_FLAG PROT_READ | PROT_WRITE
# define MAP_FLAG MAP_ANON | MAP_PRIVATE

# define TINY_MIN 1
# define TINY_MAX 992
# define SMALL_MAX 15359

# define TINY 0x1
# define SMALL 0x2
# define LARGE 0x4

# define TINY_PRE_ALLOC 30 * getpagesize()
# define SMALL_PRE_ALLOC 400 * getpagesize()

////////////////////////////////////////////////////////////////////////////////
/// STRUCTURES 
////////////////////////////////////////////////////////////////////////////////

typedef struct		s_header {
	size_t			page_size;
	struct s_header	*next;
	uint8_t			type;
}					t_header;

typedef struct		s_meta {
	uint8_t			free : 1;
	size_t			size : 31;
}					t_meta;

typedef struct		s_block {
	struct s_meta	*tiny;
	struct s_meta	*small;
}					t_block;

////////////////////////////////////////////////////////////////////////////////
/// PROTOTYPES 
////////////////////////////////////////////////////////////////////////////////

/// MALLOC

void				*malloc(size_t size);
void				*new_page(const uint8_t allocation_type, const size_t size);
void				*get_page(const uint8_t allocation_type, const size_t size);

/// FREE

void				free(void *ptr);
void				release_memory(t_header *header_ptr, t_header *previous_ptr);
void				join_memory(void *index, const void *limit);

/// REALLOC

void				*realloc(void *ptr, size_t size);
void				*new_block(void *ptr, const size_t size);
void				*expand_block(const size_t size, void *index, void *limit);

/// CALLOC

void				*calloc(size_t count, size_t size);

/// SHOW_ALLOC_MEM

void				show_alloc_mem(void);

/// LIB

void				print_str(char *str);
void				print_ptr(unsigned long long ptr);
void				print_num(size_t num);
void				*_memcpy(void *dst, const void *src, size_t n);
void				_bzero(void *s, size_t n);

/// UTILS 

t_header			**arena(void);
t_meta				**block(void);
void				create_header(const uint8_t alloc_type, const size_t page_size, void *ptr);
void				create_meta(const uint8_t status, const size_t size, void *ptr);
void				*split_block(const size_t size, void *ptr);

#endif
