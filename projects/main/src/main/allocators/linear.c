/*
#include "main/allocators/linear.h"
#include "main/collections/linked_list.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//--- private ---//
uint32_t
page_remaining_space(alloc_linear *linear) {
  void **page =
      linked_list_tail(&linear->pages);
  uintptr_t start = (uintptr_t)*page;
  uintptr_t end = start + linear->page_size;
  uintptr_t cur = (uintptr_t)linear->cur;

  return (uint32_t)(end - cur);
}

void page_add(alloc_linear *linear) {
  void *new_page = malloc(linear->page_size);
  memset(new_page, 0, linear->page_size);
  linked_list_push_back(&linear->pages,
                        &new_page);
  linear->cur = new_page;
}

void *get_aligned_ptr(void *cur,
                      uint32_t size,
                      uint32_t align) {
  uintptr_t cu = (uintptr_t)cur;
  uintptr_t aligned_cur =
      ((cu + (align - 1)) &
       ~(uintptr_t)(align - 1));
  return (void *)aligned_cur;
}

//--- alloc_linear ---//
alloc_linear *alloc_linear_make() {
  uint32_t page_size = 1024;
  assert(page_size > sizeof(alloc_linear));

  void *first_page = malloc(page_size);
  alloc_linear *linear =
      (alloc_linear *)first_page;
  linear->pages =
      linked_list_make(sizeof(void *));
  linear->cur =
      (void *)((uintptr_t)first_page +
               sizeof(alloc_linear));
  linear->page_size = page_size;
  return linear;
}

void alloc_linear_destroy(
    alloc_linear *linear) {
  uint32_t count =
      linked_list_count(&linear->pages);
  for (uint32_t i = count; i-- > 0;) {
    void **page =
        linked_list_get(&linear->pages, i);
    free(*page);
  }
  linked_list_destroy(&linear->pages);
  linear = NULL;
}

void *
alloc_linear_alloc(alloc_linear *linear,
                   uint32_t size,
                   uint32_t align) {
  assert(size != 0);
  assert(size <= linear->page_size);
  assert(align != 0);
  assert(((align - 1) & align) != 0);

  void *aligned_ptr = get_aligned_ptr(
      linear->cur, size, align);
  uintptr_t align_diff =
      (uintptr_t)aligned_ptr -
      (uintptr_t)linear->cur;
  uint32_t total_size = size + align_diff;

  assert(total_size < linear->page_size);

  if (total_size >
      page_remaining_space(linear)) {
    page_add(linear);
    aligned_ptr = get_aligned_ptr(
        linear->cur, size, align);
  }

  linear->cur =
      (void *)((uintptr_t)linear->cur +
               total_size);
  return aligned_ptr;
}
*/
