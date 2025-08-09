#include "main/collections/dyn_array.h"
#include "main/core/core.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//---dyn_array---//
/*
typedef struct {
  void *data;
  uint32_t item_size;
  uint32_t count;
  uint32_t capacity;
} dyn_array;
*/
uint32_t s_start_cap = 10;
float s_growth_rate = 1.5f;

//--- private ---//

uint32_t
get_max_capacity(uint32_t item_size) {
  return UINT32_MAX / item_size;
}

uint32_t get_new_cap(uint32_t cap,
                     uint32_t item_size) {
  uint32_t max_cap =
      get_max_capacity(item_size);
  uint32_t new_cap = 0;

  if (cap >= max_cap / s_growth_rate) {
    new_cap = max_cap;
  } else {
    new_cap = cap * s_growth_rate;
  }
  return new_cap;
}

void resize_with_cap(dyn_array *arr,
                     uint32_t new_cap) {
  assert(arr->capacity <
         get_max_capacity(arr->item_size));
  assert(new_cap <
         get_max_capacity(arr->item_size));
  assert(new_cap > arr->capacity);

  uint32_t cur_size =
      arr->item_size * arr->capacity;
  uint32_t new_size =
      arr->item_size * new_cap;

  void *new_mem = malloc(new_size);
  memset(new_mem, 0, new_size);
  if (arr->data) {
    memcpy(new_mem, arr->data, cur_size);
    free(arr->data);
  }

  arr->data = new_mem;
  arr->capacity = new_cap;
}

void resize(dyn_array *arr) {
  uint32_t new_cap = get_new_cap(
      arr->capacity, arr->item_size);
  resize_with_cap(arr, new_cap);
}

void *get_ptr_to_index(dyn_array *arr,
                       uint32_t index) {
  return (void *)((uintptr_t)arr->data +
                  (index * arr->item_size));
}
void *get_ptr_to_last(dyn_array *arr) {
  uint32_t index =
      dyn_array_count(arr) == 0
          ? 0
          : dyn_array_count(arr) - 1;
  return get_ptr_to_index(arr, index);
}
void *increment_ptr(dyn_array *arr,
                    void *ptr,
                    int32_t value) {
  return (void *)((uintptr_t)ptr +
                  (arr->item_size * value));
}

//--- dyn_array ---//
dyn_array
dyn_array_make(uint32_t item_size) {
  assert(item_size <
         UINT32_MAX / s_start_cap);
  dyn_array arr;
  arr.item_size = item_size;
  arr.count = 0;
  arr.capacity = 0;
  arr.data = NULL;
  resize_with_cap(&arr, s_start_cap);
  return arr;
}

void dyn_array_destroy(dyn_array *arr) {
  if (!arr->data) {
    return;
  }
  free(arr->data);
  arr->data = NULL;
  arr->count = 0;
  arr->capacity = 0;
  arr->item_size = 0;
}

uint32_t dyn_array_count(dyn_array *arr) {
  return arr->count;
}

uint32_t dyn_array_capacity(dyn_array *arr) {
  return arr->capacity;
}
void *dyn_array_get(dyn_array *arr,
                    uint32_t index) {
  assert(index < arr->count);
  return get_ptr_to_index(arr, index);
}

void *dyn_array_push_back(dyn_array *arr,
                          void *data) {

  assert(arr->count < UINT32_MAX);

  if (arr->count == arr->capacity) {
    resize(arr);
  }

  void *dest =
      get_ptr_to_index(arr, arr->count);
  memcpy(dest, data, arr->item_size);

  arr->count++;
  return dest;
}

void dyn_array_reserve(dyn_array *arr,
                       uint32_t count) {
  uint32_t available =
      arr->capacity - arr->count;
  if (count <= available) {
    return;
  }
  uint32_t new_cap = arr->capacity;
  while (count > available) {
    new_cap =
        get_new_cap(new_cap, arr->item_size);
    available = new_cap - arr->count;
  }
  resize_with_cap(arr, new_cap);
}

void dyn_array_override(dyn_array *arr,
                        void *data,
                        uint32_t index) {
  assert(index < arr->count);

  void *dest = get_ptr_to_index(arr, index);
  memcpy(dest, data, arr->item_size);
}

void dyn_array_insert(dyn_array *arr,
                      void *data,
                      uint32_t index) {
  assert(index < arr->count);
  if (arr->count == arr->capacity) {
    resize(arr);
  }

  uint32_t item_count_to_shift =
      arr->count - index;
  uint32_t size_of_shift =
      item_count_to_shift * arr->item_size;
  void *temp_buf = malloc(size_of_shift);

  void *src = get_ptr_to_index(arr, index);
  memcpy(temp_buf, src, size_of_shift);

  memcpy(src, data, arr->item_size);
  src = increment_ptr(arr, src, 1);
  memcpy(src, temp_buf, size_of_shift);
  arr->count++;
  free(temp_buf);
}

void dyn_array_remove(dyn_array *arr,
                      uint32_t index) {
  assert(index < arr->count);

  if (index == arr->count - 1) {
    void *ptr = get_ptr_to_index(arr, index);
    memset(ptr, 0, arr->item_size);
    arr->count--;
    return;
  }

  void *item_to_remove =
      get_ptr_to_index(arr, index);
  void *next_item =
      get_ptr_to_index(arr, index + 1);
  uint32_t size_to_copy =
      (arr->count - index - 1) *
      arr->item_size;
  void *temp_buf = malloc(size_to_copy);
  memcpy(temp_buf, next_item, size_to_copy);

  memcpy(item_to_remove, temp_buf,
         size_to_copy);
  void *last_item =
      get_ptr_to_index(arr, arr->count - 1);
  memset(last_item, 0, arr->item_size);

  arr->count--;
  free(temp_buf);
}

//--- private ---//
bool span_valid(dyn_array_span span) {
  if (!span.arr) {
    return false;
  }
  if (span.start > span.arr->count) {
    return false;
  }
  if (uint32_overflow(span.start,
                      span.count)) {
    return false;
  }
  if (span.start + span.count >
      span.arr->count) {
    return false;
  }
  return true;
}
bool span_belong_to_arr(dyn_array_span span,
                        dyn_array *arr) {
  return span.arr == arr;
}

//--- dyn_array_span ---//
dyn_array_span
dyn_array_span_make(dyn_array *arr,
                    uint32_t start,
                    uint32_t count) {
  dyn_array_span span;
  span.arr = arr;
  span.start = start;
  span.count = count;
  assert(span_valid(span));
  return span;
}

dyn_array_span
dyn_array_span_make_whole(dyn_array *arr) {
  return dyn_array_span_make(arr, 0,
                             arr->count);
}

dyn_array
dyn_array_copy(dyn_array_span span) {
  assert(span_valid(span));

  dyn_array copy_arr =
      dyn_array_make(span.arr->item_size);
  dyn_array_reserve(&copy_arr, span.count);

  void *items_to_copy =
      get_ptr_to_index(span.arr, span.start);
  uint32_t copy_size =
      (span.count) * span.arr->item_size;
  void *dest =
      get_ptr_to_index(&copy_arr, 0);
  memcpy(dest, items_to_copy, copy_size);
  copy_arr.count = span.count;

  return copy_arr;
}

void dyn_array_join_back(
    dyn_array *dest,
    dyn_array_span src_span) {
  assert(
      !span_belong_to_arr(src_span, dest));
  assert(span_valid(src_span));
  assert(dest->item_size ==
         src_span.arr->item_size);

  dyn_array_reserve(dest, src_span.count);

  void *dest_ptr =
      get_ptr_to_index(dest, dest->count);
  void *src_ptr =
      get_ptr_to_index(src_span.arr, 0);
  uint32_t size = src_span.arr->item_size *
                  src_span.count;

  memcpy(dest_ptr, src_ptr, size);
  dest->count += src_span.count;
}

void dyn_array_remove_span(
    dyn_array_span span) {
  if (span.start + span.count ==
      span.arr->count) {
    span.arr->count = span.start;
    return;
  }

  uint32_t index = span.start + span.count;
  uint32_t count = span.arr->count - index;
  dyn_array remaining =
      dyn_array_copy(dyn_array_span_make(
          span.arr, index, count));

  span.arr->count = span.start + 1;

  dyn_array_join_back(
      span.arr,
      dyn_array_span_make_whole(&remaining));
  dyn_array_destroy(&remaining);
}

void dyn_array_join(dyn_array *dest,
                    dyn_array_span src_span,
                    uint32_t index_in_dest) {

  assert(index_in_dest <= dest->count);
  assert(dest->item_size ==
         src_span.arr->item_size);
  assert(
      !span_belong_to_arr(src_span, dest));
  assert(span_valid(src_span));

  if (index_in_dest == dest->count) {
    dyn_array_join_back(dest, src_span);
    return;
  }

  dyn_array remaining =
      dyn_array_copy(dyn_array_span_make(
          dest, index_in_dest,
          dest->count - index_in_dest));
  dyn_array_remove_span(dyn_array_span_make(
      dest, index_in_dest,
      dest->count - index_in_dest));

  dyn_array_join_back(dest, src_span);
  dyn_array_join_back(
      dest,
      dyn_array_span_make_whole(&remaining));

  dyn_array_destroy(&remaining);
}
