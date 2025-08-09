#include "main/collections/str_ascii.h"
#include "main/core/core.h"

#include <stdbool.h>

/*
typedef struct {
  dyn_array data;
} str_ascii;
*/

//--- private ---//
void null_terminator_remove(str_ascii *str) {
  dyn_array_remove(&str->data,
                   str_ascii_count(str));
}

void null_terminator_add(str_ascii *str) {
  dyn_array_push_back(&(str->data),
                      &(char){'\0'});
}

//--- str_ascii ---//
str_ascii str_ascii_make(char *str) {
  str_ascii stra;
  stra.data = dyn_array_make(sizeof(char));
  if (str) {
    while (*str != '\0') {
      dyn_array_push_back(&(stra.data), str);
      str++;
    }
  }
  dyn_array_push_back(&(stra.data),
                      &(char){'\0'});
  return stra;
}

void str_ascii_destroy(str_ascii *str) {
  if (!str) {
    return;
  }
  dyn_array_destroy(&str->data);
}

char str_ascii_at(str_ascii *str,
                  uint32_t index) {
  return *(char *)dyn_array_get(&str->data,
                                index);
}
char *str_ascii_get_ptr(str_ascii *str) {
  return (char *)dyn_array_get(&str->data,
                               0);
}
uint32_t str_ascii_count(str_ascii *str) {
  return dyn_array_count(&str->data) - 1;
}

//--- private ---//
bool str_ascii_span_valid(
    str_ascii_span span) {
  if (!span.str) {
    return false;
  }
  if (span.start >
      str_ascii_count(span.str)) {
    return false;
  }
  if (uint32_overflow(span.start,
                      span.count)) {
    return false;
  }
  if (span.start + span.count >
      str_ascii_count(span.str)) {
    return false;
  }
  return true;
}
bool span_belong_to_str(str_ascii_span span,
                        str_ascii *str) {
  return span.str == str;
}

//--- str_ascii_span ---//
str_ascii_span
str_ascii_span_make(str_ascii *str,
                    uint32_t start,
                    uint32_t count) {
  str_ascii_span span;
  span.str = str;
  span.start = start;
  span.count = count;
  str_ascii_span_valid(span);
  return span;
}
str_ascii_span
str_ascii_span_make_whole(str_ascii *str) {
  return str_ascii_span_make(
      str, 0, str_ascii_count(str));
}

str_ascii
str_ascii_copy(str_ascii_span span) {
  null_terminator_remove(span.str);
  str_ascii str;
  str.data =
      dyn_array_copy(dyn_array_span_make(
          &(span.str->data), span.start,
          span.count));
  null_terminator_add(span.str);
  null_terminator_add(&str);
  return str;
}
void str_ascii_remove_span(
    str_ascii_span span) {
  null_terminator_remove(span.str);
  dyn_array_remove_span(dyn_array_span_make(
      &(span.str->data), span.start,
      span.count));

  null_terminator_add(span.str);
}

void str_ascii_join_back(
    str_ascii *dest,
    str_ascii_span src_span) {
  null_terminator_remove(dest);
  dyn_array_join_back(
      &(dest->data),
      dyn_array_span_make(
          &(src_span.str->data),
          src_span.start, src_span.count));
  null_terminator_add(dest);
}
void str_ascii_join(str_ascii *dest,
                    str_ascii_span src_span,
                    uint32_t index_in_dest) {
  null_terminator_remove(dest);
  dyn_array_join(&dest->data,
                 dyn_array_span_make(
                     &(src_span.str->data),
                     src_span.start,
                     src_span.count),
                 index_in_dest);
  null_terminator_add(dest);
}
