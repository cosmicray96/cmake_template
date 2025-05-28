#pragma once

#include "soco_dsa/allocators/allocator.h"
#include "soco_dsa/export.h"
#include "soco_dsa/collections/span.h"


size_t soco_dsa_min(soco_dsa_span span, bool (*comp_func)(void* elem1, void* elem2));
size_t soco_dsa_max(soco_dsa_span span, bool (*comp_func)(void* elem1, void* elem2));
void* soco_dsa_sum(soco_dsa_span span, void* (*add_func)(void* elem1, void* elem2));
void* soco_dsa_sum(soco_dsa_span span, void* (*add_func)(void* elem1, void* elem2));
