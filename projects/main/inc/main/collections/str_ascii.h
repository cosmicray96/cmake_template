#ifndef STR_ASCII_H
#define STR_ASCII_H

#include "main/collections/dyn_array.h"

//--- structs ---//
typedef struct {
  dyn_array data;
} str_ascii;

typedef struct {
  str_ascii *str;
  uint32_t start;
  uint32_t count;
} str_ascii_span;

//--- str_ascii ---//
str_ascii str_ascii_make(char *str);
void str_ascii_destroy(str_ascii *str);

char str_ascii_at(str_ascii *str,
                  uint32_t index);
char *str_ascii_get_ptr(str_ascii *str);
uint32_t str_ascii_count(str_ascii *str);

//--- str_ascii_span ---//
str_ascii_span
str_ascii_span_make(str_ascii *str,
                    uint32_t start,
                    uint32_t count);
str_ascii_span
str_ascii_span_make_whole(str_ascii *str);

str_ascii
str_ascii_copy(str_ascii_span span);
void str_ascii_remove_span(
    str_ascii_span span);

void str_ascii_join_back(
    str_ascii *dest,
    str_ascii_span src_span);
void str_ascii_join(str_ascii *dest,
                    str_ascii_span src_span,
                    uint32_t index_in_dest);

#endif
