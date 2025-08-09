#ifndef CORE_CORE_H
#define CORE_CORE_H

#include <stdbool.h>
#include <stdint.h>

static bool uint32_overflow(uint32_t a,
                            uint32_t b) {
  return a + b < a;
}

#endif
