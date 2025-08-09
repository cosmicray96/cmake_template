#ifndef ALLOCATORS_LINEAR_H
#define ALLOCATORS_LINEAR_H

#include <stdint.h>

#include "main/allocators/allocator.h"
#include "main/collections/linked_list.h"

typedef struct {
  linked_list pages;
  void *cur;
  uint32_t page_size;
} alloc_linear;

alloc_linear *alloc_linear_make();
void alloc_linear_destroy(
    alloc_linear *linear);

allocator alloc_linear_to_allocator(
    alloc_linear *linear);

void alloc_linear_reset(
    alloc_linear *linear);
void *
alloc_linear_alloc(alloc_linear *linear,
                   uint32_t size,
                   uint32_t align);

#endif
