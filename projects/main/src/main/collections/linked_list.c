#include "main/collections/linked_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--- struct ---//

/*
typedef struct {
  ll_node *next;
  void *data;
}ll_node ;

typedef struct {
  ll_node *head;
  ll_node *tail;
  uint32_t item_size;
  uint32_t count;
} linked_list;
*/

//--- ll_node ---//
ll_node *ll_node_make(void *data,
                      uint32_t item_size) {
  ll_node *new_node =
      malloc(sizeof(ll_node));
  new_node->data = malloc(item_size);
  memcpy(new_node->data, data, item_size);
  new_node->next = NULL;
  return new_node;
}

void ll_node_destroy(ll_node *node) {

  free(node->data);
  node->next = NULL;
  node->data = NULL;
  free(node);
}

void *ll_node_data(ll_node *node) {
  return node->data;
}

//--- private ---//
void push_first_node(linked_list *ll,
                     ll_node *first_node) {
  assert(ll->count == 0);

  ll->head = first_node;
  ll->tail = first_node;
  ll->count = 1;
}
void pop_last_node(linked_list *ll) {
  assert(ll->count == 1);

  ll_node_destroy(ll->head);
  ll->head = NULL;
  ll->tail = NULL;
  ll->count = 0;
}

ll_node *
linked_list_get_node(linked_list *ll,
                     uint32_t index) {
  assert(index < ll->count);
  if (index == 0) {
    return ll->head;
  }
  if (index == ll->count - 1) {
    return ll->tail;
  }

  uint32_t i = 0;
  ll_node *cur = ll->head;
  while (i != index) {
    cur = cur->next;
    i++;
  }
  return cur;
}

void push_node_front(linked_list *ll,
                     ll_node *new_node) {
  if (!ll->head) {
    push_first_node(ll, new_node);
    return;
  }
  new_node->next = ll->head;
  ll->head = new_node;
  ll->count++;
}
void push_node_back(linked_list *ll,
                    ll_node *new_node) {
  if (!ll->tail) {
    push_first_node(ll, new_node);
    return;
  }
  ll->tail->next = new_node;
  ll->tail = new_node;
  ll->count++;
}
void push_node(linked_list *ll,
               ll_node *new_node,
               uint32_t index) {
  assert(index < ll->count);

  if (index == 0) {
    push_node_front(ll, new_node);
    return;
  }

  ll_node *cur =
      linked_list_get_node(ll, index - 1);
  ll_node *next = cur->next;
  cur->next = new_node;
  new_node->next = next;
  ll->count++;
}

//--- linked_list ---//
void linked_list_make(linked_list *location,
                      uint32_t item_size) {
  assert(item_size > 0);
  linked_list *ll = location;
  ll->head = NULL;
  ll->tail = NULL;
  ll->item_size = item_size;
  ll->count = 0;
}
void linked_list_destroy(linked_list *ll) {
  if (!ll->head) {
    return;
  }

  ll_node *cur = ll->head;
  while (cur != NULL) {
    ll_node *next = cur->next;
    ll_node_destroy(cur);
    cur = next;
  }

  ll->head = NULL;
  ll->tail = NULL;
  ll->count = 0;
}

//--- Insert ---//
void linked_list_push_front(linked_list *ll,
                            void *data) {
  ll_node *new_node =
      ll_node_make(data, ll->item_size);
  push_node_front(ll, new_node);
}
void linked_list_push_back(linked_list *ll,
                           void *data) {
  ll_node *new_node =
      ll_node_make(data, ll->item_size);
  push_node_back(ll, new_node);
}
void linked_list_push(linked_list *ll,
                      void *data,
                      uint32_t index) {
  ll_node *new_node =
      ll_node_make(data, ll->item_size);
  push_node(ll, new_node, index);
}

//--- Remove ---//
void linked_list_pop_front(linked_list *ll) {

  assert(ll->count > 0);

  if (ll->count == 1) {
    pop_last_node(ll);
    return;
  }
  ll_node *new_head = ll->head->next;
  ll_node_destroy(ll->head);
  ll->head = new_head;
  ll->count--;
}
void linked_list_pop_back(linked_list *ll) {
  assert(ll->count > 0);

  if (ll->count == 1) {
    pop_last_node(ll);
    return;
  }

  ll_node *tail_parent =
      linked_list_get_node(ll,
                           ll->count - 2);
  tail_parent->next = NULL;
  ll_node_destroy(ll->tail);
  ll->tail = tail_parent;
  ll->count--;
}
void linked_list_pop(linked_list *ll,
                     uint32_t index) {
  assert(ll->count > 0);
  assert(index < ll->count);

  if (index == ll->count - 1) {
    linked_list_pop_back(ll);
    return;
  }

  if (index == 0) {
    linked_list_pop_front(ll);
    return;
  }

  ll_node *parent =
      linked_list_get_node(ll, index - 1);
  ll_node *node_to_pop = parent->next;
  parent->next = node_to_pop->next;
  ll_node_destroy(node_to_pop);
  ll->count--;
}

//--- Get ---//
uint32_t linked_list_count(linked_list *ll) {
  return ll->count;
}
void *linked_list_head(linked_list *ll) {
  return ll_node_data(ll->head);
}
void *linked_list_tail(linked_list *ll) {
  return ll_node_data(ll->tail);
}
void *linked_list_get(linked_list *ll,
                      uint32_t index) {

  return ll_node_data(
      linked_list_get_node(ll, index));
}
