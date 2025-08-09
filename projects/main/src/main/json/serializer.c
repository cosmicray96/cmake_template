#include "main/json/serializer.h"

#include "main/collections/dyn_array.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--- Types ---//

typedef enum {
  json_item_int,
  json_item_float,
  json_item_string,
  json_item_obj,
  json_item_array,
  json_item_null,
  json_item_bool
} json_item_type;

typedef struct json_item json_item;
struct json_item {
  union {
    int32_t int_val;
    float float_val;
    char *str_val;
    bool bool_val;
    struct {
      json_item *parent;
      dyn_array items;
    } obj_val;
    struct {
      json_item *parent;
      dyn_array items;
    } arr_val;
  } value;
  char *name;
  json_item_type type;
};

struct json_ctx {
  json_item root;
  json_item *cur_parent;
};

void json_item_set_name(json_item *item,
                        char *name) {
  if (!name) {
    item->name = NULL;
    return;
  }
  size_t name_length = strlen(name) + 1;
  char *item_name =
      (char *)malloc(name_length);
  strcpy(item_name, name);
  item->name = item_name;
}

json_item *
link_parent_child(json_item *parent,
                  json_item *child) {
  json_item *correct_child;
  switch (parent->type) {
  case json_item_obj: {
    dyn_array *arr =
        &(parent->value.obj_val.items);
    correct_child =
        dyn_array_push_back(arr, child);
    break;
  }
  case json_item_array: {
    dyn_array *arr =
        &(parent->value.arr_val.items);
    correct_child =
        dyn_array_push_back(arr, child);
    break;
  }
  default:
    assert(false);
    break;
  }
  switch (child->type) {
  case json_item_obj: {
    correct_child->value.obj_val.parent =
        parent;
    break;
  }
  case json_item_array: {
    correct_child->value.arr_val.parent =
        parent;
    break;
  }
  default: {
    break;
  }
  }
  return correct_child;
}

void end_scope(json_ctx *ctx) {
  json_item *cur = ctx->cur_parent;
  switch (cur->type) {
  case json_item_obj: {
    json_item *parent =
        cur->value.obj_val.parent;
    ctx->cur_parent = parent;
    break;
  }
  case json_item_array: {
    json_item *parent =
        cur->value.arr_val.parent;
    ctx->cur_parent = parent;
    break;
  }
  default:
    assert(false);
    break;
  }
}

//--- json_obj ---//
json_item *json_obj_make(json_item *ptr,
                         char *name) {
  json_item *item = ptr;
  item->type = json_item_obj;
  item->value.obj_val.parent = NULL;
  item->value.obj_val.items =
      dyn_array_make(sizeof(json_item));
  json_item_set_name(item, name);
  return item;
}

//--- json_array ---//
json_item *json_array_make(json_item *ptr,
                           char *name) {
  json_item *item = ptr;
  item->type = json_item_array;
  item->value.arr_val.parent = NULL;
  item->value.arr_val.items =
      dyn_array_make(sizeof(json_item));
  json_item_set_name(item, name);
  return item;
}

//--- json_ctx ---//
json_ctx *json_serializer_make() {
  json_ctx *ctx = malloc(sizeof(json_ctx));
  json_obj_make(&ctx->root, NULL);
  ctx->cur_parent = &ctx->root;
  return ctx;
}

void json_serializer_destroy(json_ctx *ctx) {
  // recirsively delete
}

void json_serializer_int(json_ctx *ctx,
                         char *name,
                         int32_t value) {
  json_item item;
  item.type = json_item_int;
  json_item_set_name(&item, name);
  item.value.int_val = value;
  link_parent_child(ctx->cur_parent, &item);
}

void json_serializer_float(json_ctx *ctx,
                           char *name,
                           float value) {
  json_item item;
  item.type = json_item_float;
  json_item_set_name(&item, name);
  item.value.float_val = value;
  link_parent_child(ctx->cur_parent, &item);
}
void json_serializer_string(json_ctx *ctx,
                            char *name,
                            char *value) {
  json_item item;
  item.type = json_item_string;
  json_item_set_name(&item, name);
  size_t value_length = strlen(value) + 1;
  char *value_copy =
      (char *)malloc(value_length);
  strcpy(value_copy, value);
  item.value.str_val = value_copy;
  link_parent_child(ctx->cur_parent, &item);
}

void json_serializer_bool(json_ctx *ctx,
                          char *name,
                          bool value) {
  json_item item;
  item.type = json_item_bool;
  json_item_set_name(&item, name);
  item.value.bool_val = value;
  link_parent_child(ctx->cur_parent, &item);
}

void json_serializer_null(json_ctx *ctx,
                          char *name) {
  json_item item;
  item.type = json_item_null;
  json_item_set_name(&item, name);
  link_parent_child(ctx->cur_parent, &item);
}

void json_serializer_obj_begin(json_ctx *ctx,
                               char *name) {

  json_item item;
  json_obj_make(&item, name);
  json_item *correct_child =
      link_parent_child(ctx->cur_parent,
                        &item);
  ctx->cur_parent = correct_child;
}

void json_serializer_obj_end(json_ctx *ctx) {

  if (ctx->cur_parent->type !=
      json_item_obj) {
    assert(false);
  }
  end_scope(ctx);
}

void json_serializer_array_begin(
    json_ctx *ctx, char *name) {
  json_item item;
  json_array_make(&item, name);
  json_item *correct_child =
      link_parent_child(ctx->cur_parent,
                        &item);
  ctx->cur_parent = correct_child;
}

void json_serializer_array_end(
    json_ctx *ctx) {
  if (ctx->cur_parent->type !=
      json_item_array) {
    assert(false);
  }
  end_scope(ctx);
}

//--- Print ---//
void json_serializer_print_int(
    json_item *item, bool add_begin_comma) {
  if (add_begin_comma) {
    printf(",");
  }
  if (item->name) {
    printf("\"%s\":", item->name);
  }
  printf("%d \n", item->value.int_val);
}
void json_serializer_print_float(
    json_item *item, bool add_begin_comma) {
  if (add_begin_comma) {
    printf(",");
  }
  if (item->name) {
    printf("\"%s\":", item->name);
  }
  printf("%f\n", item->value.float_val);
}
void json_serializer_print_string(
    json_item *item, bool add_begin_comma) {
  if (add_begin_comma) {
    printf(",");
  }
  if (item->name) {
    printf("\"%s\":", item->name);
  }
  printf("\"%s\"\n", item->value.str_val);
}
void json_serializer_print_bool(
    json_item *item, bool add_begin_comma) {
  if (add_begin_comma) {
    printf(",");
  }
  if (item->name) {
    printf("\"%s\":", item->name);
  }
  if (item->value.bool_val) {
    printf("true\n");
  } else {
    printf("false\n");
  }
}
void json_serializer_print_null(
    json_item *item, bool add_begin_comma) {
  if (add_begin_comma) {
    printf(",");
  }
  if (item->name) {
    printf("\"%s\":", item->name);
  }
  printf("null\n");
}

void json_serializer_print_item(
    json_item *item, bool add_begin_comma);
void json_serializer_print_obj(
    json_item *item, bool add_begin_comma) {
  if (add_begin_comma) {
    printf(",");
  }
  uint32_t count = dyn_array_count(
      &item->value.obj_val.items);

  if (item->name) {
    printf("\"%s\":", item->name);
  }
  printf("{\n");

  if (count > 0) {
    json_item *first_child = dyn_array_get(
        &item->value.obj_val.items, 0);
    json_serializer_print_item(first_child,
                               false);
  }
  for (uint32_t i = 1; i < count; i++) {
    json_item *child = dyn_array_get(
        &item->value.obj_val.items, i);
    json_serializer_print_item(child, true);
  }

  printf("}\n");
}
void json_serializer_print_array(
    json_item *item, bool add_begin_comma) {
  uint32_t count = dyn_array_count(
      &item->value.arr_val.items);
  if (add_begin_comma) {
    printf(",");
  }

  if (item->name) {
    printf("\"%s\":", item->name);
  }
  printf("[\n");

  if (count > 0) {
    json_item *first_child = dyn_array_get(
        &item->value.arr_val.items, 0);
    json_serializer_print_item(first_child,
                               false);
  }
  for (uint32_t i = 0; i < count; i++) {
    json_item *child = dyn_array_get(
        &item->value.arr_val.items, i);
    json_serializer_print_item(child, true);
  }

  printf("]\n");
}

void json_serializer_print_item(
    json_item *item, bool add_begin_comma) {
  switch (item->type) {
  case json_item_int:
    json_serializer_print_int(
        item, add_begin_comma);
    return;
  case json_item_float:
    json_serializer_print_float(
        item, add_begin_comma);
    return;
  case json_item_string:
    json_serializer_print_string(
        item, add_begin_comma);
    return;
  case json_item_bool:
    json_serializer_print_bool(
        item, add_begin_comma);
    return;
  case json_item_null:
    json_serializer_print_null(
        item, add_begin_comma);
    return;
  case json_item_obj:
    json_serializer_print_obj(
        item, add_begin_comma);
    return;
  case json_item_array:
    json_serializer_print_array(
        item, add_begin_comma);
    return;
  default:
    assert(false);
    return;
  }
}

void json_serializer_print(json_ctx *ctx) {
  json_serializer_print_obj(&ctx->root,
                            false);
}
