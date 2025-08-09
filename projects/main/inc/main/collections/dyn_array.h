#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include <stdint.h>

//--- structs ---//
typedef struct {
  void *data;
  uint32_t item_size;
  uint32_t count;
  uint32_t capacity;
} dyn_array;

typedef struct {
  dyn_array *arr;
  uint32_t start;
  uint32_t count;
} dyn_array_span;

/*
typedef struct {
  dyn_array* arr;
  dyn_array indexes;
};
*/

//--- dyn_array ---//
dyn_array dyn_array_make(uint32_t item_size);
void dyn_array_destroy(dyn_array *arr);

uint32_t dyn_array_count(dyn_array *arr);
uint32_t dyn_array_capacity(dyn_array *arr);
void *dyn_array_get(dyn_array *arr,
                    uint32_t index);

void *dyn_array_push_back(dyn_array *arr,
                          void *data);
void dyn_array_override(dyn_array *arr,
                        void *data,
                        uint32_t index);
void dyn_array_insert(dyn_array *arr,
                      void *data,
                      uint32_t index);

void dyn_array_remove(dyn_array *arr,
                      uint32_t index);

void dyn_array_reserve(dyn_array *arr,
                       uint32_t count);

//--- dyn_array_span ---//
dyn_array_span
dyn_array_span_make(dyn_array *arr,
                    uint32_t start,
                    uint32_t count);
dyn_array_span
dyn_array_span_make_whole(dyn_array *arr);

dyn_array
dyn_array_copy(dyn_array_span span);
void dyn_array_remove_span(
    dyn_array_span span);

void dyn_array_join_back(
    dyn_array *dest,
    dyn_array_span src_span);
void dyn_array_join(dyn_array *dest,
                    dyn_array_span src_span,
                    uint32_t index_in_dest);

#endif
