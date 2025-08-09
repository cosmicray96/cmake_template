/*
#include "main/allocators/linear.h"

#include <stdint.h>
#include <stdlib.h>

struct alloc_linear {
  void *base;
  void *cur;
  uint32_t total_size;
};

//--- private ---//
uint32_t
remaining_space(alloc_linear *linear) {
  uintptr_t start = (uintptr_t)linear->base;
  uintptr_t current = (uintptr_t)linear->cur;
  uintptr_t end = start + linear->total_size;
  return (uint32_t)(end - current);
}

//--- alloc_linear ---//
alloc_linear *alloc_linear_make() {
  void *data = malloc(1024);
  alloc_linear *linear =
      (alloc_linear *)data;
  linear->base = data;
  linear->total_size = 1024;
  linear->cur =
      (void *)((uintptr_t)data +
               sizeof(alloc_linear));
  return linear;
}
void alloc_linear_destroy(
    alloc_linear *linear) {
  free(linear);
}

void dealloc(alloc_linear *alloc,
             void *ptr) {}
allocator alloc_linear_to_allocator(
    alloc_linear *linear) {
  return allocator{.alloc =
                       &alloc_linear_alloc,
                   .dealloc = &dealloc};
}

void alloc_linear_reset(
    alloc_linear *linear) {
  linear->cur =
      linear->base + sizeof(alloc_linear);
}

void *
alloc_linear_alloc(alloc_linear *linear,
                   uint32_t size,
                   uint32_t align) {
  if (size == 0) {
    return NULL;
  }
  if (((align - 1) & align) != 0 ||
      align == 0) {
    return NULL;
  }

  uintptr_t cur = (uintptr_t)linear->cur;
  uintptr_t aligned_cur =
      ((cur + (align - 1)) &
       ~(uintptr_t)(align - 1));
  uintptr_t align_diff = aligned_cur - cur;

  if (remaining_space(linear) <
      align_diff + size) {
    return NULL;
  }

  linear->cur = (void *)(aligned_cur + size);
  return (void *)aligned_cur;
}
*/
