#ifndef JSON_SERIALIZER
#define JSON_SERIALIZER

#include <stdbool.h>
#include <stdint.h>

typedef struct json_ctx json_ctx;

json_ctx *json_serializer_make();
void json_serializer_destroy(json_ctx *ctx);

void json_serializer_int(json_ctx *ctx,
                         char *name,
                         int32_t value);
void json_serializer_float(json_ctx *ctx,
                           char *name,
                           float value);
void json_serializer_string(json_ctx *ctx,
                            char *name,
                            char *value);
void json_serializer_bool(json_ctx *ctx,
                          char *name,
                          bool value);
void json_serializer_null(json_ctx *ctx,
                          char *name);

void json_serializer_obj_begin(json_ctx *ctx,
                               char *name);
void json_serializer_obj_end(json_ctx *ctx);

void json_serializer_array_begin(
    json_ctx *ctx, char *name);
void json_serializer_array_end(
    json_ctx *ctx);

void json_serializer_print(json_ctx *ctx);

#endif
