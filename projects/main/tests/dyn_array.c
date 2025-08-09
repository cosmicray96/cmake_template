
#include "main/collections/dyn_array.h"

#include <assert.h>
#include <stdio.h>

int main() {

  printf("testing "
         "collections/test_array_dyn.c\n");
  {
    printf("basic make");
    dyn_array arr =
        dyn_array_make(sizeof(int32_t));
    assert(dyn_array_count(&arr) == 0);
    assert(dyn_array_capacity(&arr) == 10);
    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("dyn_array_push_back");
    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(&arr,
                          &(int32_t){10});
    }
    assert(dyn_array_count(&arr) == 10);
    assert(dyn_array_capacity(&arr) == 10);

    dyn_array_destroy(&arr);
    printf(", done!\n");
  }

  {
    printf("dyn_array_resize");

    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(&arr,
                          &(int32_t){10});
    }
    dyn_array_push_back(&arr,
                        &(int32_t){10});

    assert(dyn_array_count(&arr) == 11);
    assert(dyn_array_capacity(&arr) == 15);
    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("basic access");

    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr, &(int32_t){i * 1234});
    }

    for (int32_t i = 0; i < 10; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr, i);
      assert(value == i * 1234);
    }

    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("access with resize");

    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 12; i++) {
      dyn_array_push_back(
          &arr, &(int32_t){i * 1234});
    }

    for (int32_t i = 0; i < 12; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr, i);
      assert(value == i * 1234);
    }

    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("dyn_array_insert in middle");

    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 4; i++) {
      dyn_array_push_back(
          &arr, &(int32_t){i * 1234});
    }

    dyn_array_insert(&arr, &(int32_t){64},
                     2);

    assert(dyn_array_count(&arr) == 5);
    assert(dyn_array_capacity(&arr) == 10);

    int32_t value =
        *(int32_t *)dyn_array_get(&arr, 2);

    assert(value == 64);

    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("dyn_array_insert in start");

    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 4; i++) {
      dyn_array_push_back(
          &arr, &(int32_t){i * 1234});
    }

    dyn_array_insert(&arr, &(int32_t){64},
                     0);

    assert(dyn_array_count(&arr) == 5);
    assert(dyn_array_capacity(&arr) == 10);

    int32_t value =
        *(int32_t *)dyn_array_get(&arr, 0);

    assert(value == 64);

    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("dyn_array_insert in end");

    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 4; i++) {
      dyn_array_push_back(
          &arr, &(int32_t){i * 1234});
    }

    dyn_array_insert(&arr, &(int32_t){64},
                     3);

    assert(dyn_array_count(&arr) == 5);
    assert(dyn_array_capacity(&arr) == 10);

    for (int32_t i = 0; i < 3; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr, i);
      assert(value == i * 1234);
    }

    int32_t value =
        *(int32_t *)dyn_array_get(&arr, 3);
    assert(value == 64);

    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("dyn_array_insert causes "
           "resize");

    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr, &(int32_t){i * 1234});
    }

    dyn_array_insert(&arr, &(int32_t){64},
                     3);

    assert(dyn_array_count(&arr) == 11);
    assert(dyn_array_capacity(&arr) == 15);

    int32_t value =
        *(int32_t *)dyn_array_get(&arr, 3);

    assert(value == 64);

    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("dyn_array_remove in middle");

    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr, &(int32_t){i * 1234});
    }

    dyn_array_remove(&arr, 4);

    assert(dyn_array_count(&arr) == 9);

    for (int32_t i = 0; i < 4; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr, i);
      assert(value == i * 1234);
    }

    for (int32_t i = 4; i < 9; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr, i);
      assert(value == (i + 1) * 1234);
    }

    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("dyn_array_remove in start");

    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr, &(int32_t){i * 1234});
    }

    dyn_array_remove(&arr, 0);

    assert(dyn_array_count(&arr) == 9);

    for (int32_t i = 0; i < 9; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr, i);
      assert(value == (i + 1) * 1234);
    }

    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("dyn_array_remove in end");

    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr, &(int32_t){i * 1234});
    }

    dyn_array_remove(&arr, 9);

    assert(dyn_array_count(&arr) == 9);

    for (int32_t i = 0; i < 9; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr, i);
      assert(value == (i) * 1234);
    }

    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("override");

    dyn_array arr =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr, &(int32_t){i * 1234});
    }

    dyn_array_override(&arr, &(int32_t){10},
                       4);

    for (int32_t i = 0; i < 4; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr, i);
      assert(value == (i) * 1234);
    }
    int32_t value4 =
        *(int32_t *)dyn_array_get(&arr, 4);
    assert(value4 == 10);

    for (int32_t i = 5; i < 10; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr, i);
      assert(value == (i) * 1234);
    }

    dyn_array_destroy(&arr);
    printf(", done!\n");
  }
  {
    printf("join_back");

    dyn_array arr1 =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr1, &(int32_t){i * 10});
    }

    dyn_array arr2 =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr2, &(int32_t){i * 1234});
    }

    dyn_array_join_back(
        &arr1,
        dyn_array_span_make_whole(&arr2));

    assert(dyn_array_count(&arr1) == 20);
    assert(dyn_array_count(&arr2) == 10);

    for (int32_t i = 0; i < 10; i++) {
      int32_t value = *(
          int32_t *)dyn_array_get(&arr1, i);
      assert(value == (i) * 10);
    }
    for (int32_t i = 0; i < 10; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr1,
                                    10 + i);
      assert(value == (i) * 1234);
    }

    dyn_array_destroy(&arr2);
    dyn_array_destroy(&arr1);
    printf(", done!\n");
  }
  {
    printf("join_back dest empty");

    dyn_array arr1 =
        dyn_array_make(sizeof(int32_t));
    dyn_array arr2 =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr2, &(int32_t){i * 1234});
    }

    dyn_array_join_back(
        &arr1,
        dyn_array_span_make_whole(&arr2));

    assert(dyn_array_count(&arr1) == 10);
    assert(dyn_array_count(&arr2) == 10);

    for (int32_t i = 0; i < 10; i++) {
      int32_t value = *(
          int32_t *)dyn_array_get(&arr1, i);
      assert(value == (i) * 1234);
    }

    dyn_array_destroy(&arr2);
    dyn_array_destroy(&arr1);
    printf(", done!\n");
  }
  {
    printf("join_back src empty");

    dyn_array arr1 =
        dyn_array_make(sizeof(int32_t));
    dyn_array arr2 =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr1, &(int32_t){i * 1234});
    }

    dyn_array_join_back(
        &arr1,
        dyn_array_span_make_whole(&arr2));

    assert(dyn_array_count(&arr1) == 10);
    assert(dyn_array_count(&arr2) == 0);

    for (int32_t i = 0; i < 10; i++) {
      int32_t value = *(
          int32_t *)dyn_array_get(&arr1, i);
      assert(value == (i) * 1234);
    }

    dyn_array_destroy(&arr2);
    dyn_array_destroy(&arr1);
    printf(", done!\n");
  }
  {
    printf("join");

    dyn_array arr1 =
        dyn_array_make(sizeof(int32_t));
    dyn_array arr2 =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr1, &(int32_t){i * 10});
    }

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr2, &(int32_t){i * 1234});
    }

    dyn_array_join(
        &arr1,
        dyn_array_span_make_whole(&arr2), 5);

    assert(dyn_array_count(&arr1) == 20);
    assert(dyn_array_count(&arr2) == 10);

    for (int32_t i = 0; i < 5; i++) {
      int32_t value = *(
          int32_t *)dyn_array_get(&arr1, i);
      assert(value == (i) * 10);
    }
    for (int32_t i = 0; i < 10; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr1,
                                    5 + i);
      assert(value == (i) * 1234);
    }
    for (int32_t i = 5; i < 10; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr1,
                                    10 + i);
      assert(value == (i) * 10);
    }

    dyn_array_destroy(&arr2);
    dyn_array_destroy(&arr1);
    printf(", done!\n");
  }
  {
    printf("join at start");

    dyn_array arr1 =
        dyn_array_make(sizeof(int32_t));
    dyn_array arr2 =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr1, &(int32_t){i * 10});
    }

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr2, &(int32_t){i * 1234});
    }

    dyn_array_join(
        &arr1,
        dyn_array_span_make_whole(&arr2), 0);

    assert(dyn_array_count(&arr1) == 20);
    assert(dyn_array_count(&arr2) == 10);

    for (int32_t i = 0; i < 10; i++) {
      int32_t value = *(
          int32_t *)dyn_array_get(&arr1, i);
      assert(value == (i) * 1234);
    }
    for (int32_t i = 0; i < 10; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr1,
                                    10 + i);
      assert(value == (i) * 10);
    }

    dyn_array_destroy(&arr2);
    dyn_array_destroy(&arr1);
    printf(", done!\n");
  }
  {
    printf("join at end-1");

    dyn_array arr1 =
        dyn_array_make(sizeof(int32_t));
    dyn_array arr2 =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr1, &(int32_t){i * 10});
    }

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr2, &(int32_t){i * 1234});
    }

    dyn_array_join(
        &arr1,
        dyn_array_span_make_whole(&arr2), 9);

    assert(dyn_array_count(&arr1) == 20);
    assert(dyn_array_count(&arr2) == 10);

    for (int32_t i = 0; i < 9; i++) {
      int32_t value = *(
          int32_t *)dyn_array_get(&arr1, i);
      assert(value == (i) * 10);
    }
    for (int32_t i = 0; i < 9; i++) {
      int32_t value =
          *(int32_t *)dyn_array_get(&arr1,
                                    9 + i);
      assert(value == (i) * 1234);
    }
    int32_t value9 =
        *(int32_t *)dyn_array_get(&arr1, 19);
    assert(value9 == 90);

    dyn_array_destroy(&arr2);
    dyn_array_destroy(&arr1);
    printf(", done!\n");
  }
  {
    printf("join dest empty");

    dyn_array arr1 =
        dyn_array_make(sizeof(int32_t));
    dyn_array arr2 =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr2, &(int32_t){i * 1234});
    }

    dyn_array_join(
        &arr1,
        dyn_array_span_make_whole(&arr2), 0);

    assert(dyn_array_count(&arr1) == 10);
    assert(dyn_array_count(&arr2) == 10);

    for (int32_t i = 0; i < 10; i++) {
      int32_t value = *(
          int32_t *)dyn_array_get(&arr1, i);
      assert(value == (i) * 1234);
    }

    dyn_array_destroy(&arr2);
    dyn_array_destroy(&arr1);
    printf(", done!\n");
  }
  {
    printf("join src empty");

    dyn_array arr1 =
        dyn_array_make(sizeof(int32_t));
    dyn_array arr2 =
        dyn_array_make(sizeof(int32_t));

    for (int32_t i = 0; i < 10; i++) {
      dyn_array_push_back(
          &arr1, &(int32_t){i * 10});
    }

    dyn_array_join(
        &arr1,
        dyn_array_span_make_whole(&arr2), 0);

    assert(dyn_array_count(&arr1) == 10);
    assert(dyn_array_count(&arr2) == 0);

    for (int32_t i = 0; i < 10; i++) {
      int32_t value = *(
          int32_t *)dyn_array_get(&arr1, i);
      assert(value == (i) * 10);
    }

    dyn_array_destroy(&arr2);
    dyn_array_destroy(&arr1);
    printf(", done!\n");
  }
  printf("done testing "
         "collections/test_array_dyn.c\n");
  return 0;
}
