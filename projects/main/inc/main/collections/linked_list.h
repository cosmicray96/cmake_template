#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>

typedef struct ll_node ll_node;
struct ll_node {
  ll_node *next;
  void *data;
};

typedef struct {

  ll_node *head;
  ll_node *tail;
  uint32_t item_size;
  uint32_t count;
} linked_list;

void linked_list_make(linked_list *location,
                      uint32_t item_size);
void linked_list_destroy(linked_list *ll);

//--- Insert ---//
void linked_list_push_front(linked_list *ll,
                            void *data);
void linked_list_push_back(linked_list *ll,
                           void *data);
void linked_list_push(linked_list *ll,
                      void *data,
                      uint32_t index);

//--- Remove ---//
void linked_list_pop_front(linked_list *ll);
void linked_list_pop_back(linked_list *ll);
void linked_list_pop(linked_list *ll,
                     uint32_t index);

//--- Get ---//
uint32_t linked_list_count(linked_list *ll);
void *linked_list_head(linked_list *ll);
void *linked_list_tail(linked_list *ll);
void *linked_list_get(linked_list *ll,
                      uint32_t index);

#endif
