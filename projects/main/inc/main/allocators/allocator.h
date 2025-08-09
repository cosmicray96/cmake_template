#ifndef ALLOCATOR_H
#define ALLOCATOR_H

typedef void *(*allocator_alloc_fn)(
    void *ctx, uint32_t size,
    uint32_t align);
typedef void (*allocator_dealloc_fn)(
    void *ctx, void *ptr);

typedef struct {
  allocator_alloc_fn alloc;
  allocator_dealloc_fn dealloc;
} allocator_vt;

typedef struct {
  allocator_vt *vt;
  void *ctx;
} allocator;

#endif
