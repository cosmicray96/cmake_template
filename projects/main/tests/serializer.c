#include "main/json/serializer.h"

#include <stdio.h>

int main() {

  printf("testing json_seralizer\n");
  {
    json_ctx *ctx = json_serializer_make();

    json_serializer_int(ctx, "hello", 10);
    json_serializer_float(ctx, "world",
                          2.3f);
    json_serializer_string(ctx, "Hello",
                           "World");

    json_serializer_obj_begin(ctx,
                              "new obj");

    json_serializer_int(ctx, "hello", 10);
    json_serializer_float(ctx, "world",
                          2.3f);
    json_serializer_string(ctx, "Hello",
                           "World");

    json_serializer_obj_end(ctx);

    json_serializer_array_begin(ctx,
                                "My Array");
    json_serializer_int(ctx, NULL, 10);
    json_serializer_int(ctx, NULL, 20);
    json_serializer_int(ctx, NULL, 30);

    json_serializer_float(ctx, NULL, 3.23f);
    json_serializer_string(ctx, NULL,
                           "New Hello");

    json_serializer_obj_begin(ctx, NULL);
    json_serializer_bool(ctx, "my bool",
                         true);
    json_serializer_bool(ctx, "false false",
                         false);
    json_serializer_null(ctx, "null value");
    json_serializer_int(ctx, "hello", 10);
    json_serializer_float(ctx, "world",
                          2.3f);
    json_serializer_string(ctx, "Hello",
                           "World");
    json_serializer_obj_end(ctx);

    json_serializer_obj_begin(ctx, NULL);
    json_serializer_int(ctx, "hello", 10);
    json_serializer_float(ctx, "world",
                          2.3f);
    json_serializer_string(ctx, "Hello",
                           "World");
    json_serializer_string(ctx, "Hello2",
                           "World2");
    json_serializer_obj_end(ctx);

    json_serializer_array_end(ctx);

    json_serializer_print(ctx);
  }

  return 0;
}
