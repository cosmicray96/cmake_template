#include "main/collections/linked_list.h"

#include <assert.h>
#include <stdio.h>
void print_green(char *msg) {
  printf("\033[32m%s\033[0m", msg);
  fflush(stdout);
}
void print_test_name(char *msg) {
  print_green(">");
  printf("%s", msg);
  fflush(stdout);
}

int main() {
  printf("testing "
         "collections/test_array_dyn.c\n");

  {
    print_test_name("basic make, ");
    linked_list ll;
    linked_list_make(&ll, sizeof(uint32_t));

    assert(linked_list_count(&ll) == 0);

    linked_list_destroy(&ll);
    print_green("done!\n");
  }
  {
    print_test_name(
        "linked_list_push_front, ");
    linked_list ll;
    linked_list_make(&ll, sizeof(uint32_t));

    assert(linked_list_count(&ll) == 0);
    linked_list_push_front(&ll,
                           &(uint32_t){10});
    assert(linked_list_count(&ll) == 1);

    assert(
        10 ==
        *(uint32_t *)linked_list_head(&ll));
    assert(
        10 ==
        *(uint32_t *)linked_list_tail(&ll));
    assert(10 ==
           *(uint32_t *)linked_list_get(&ll,
                                        0));

    linked_list_destroy(&ll);
    print_green("done!\n");
  }
  {
    print_test_name(
        "linked_list_push_front many, ");
    linked_list ll;
    linked_list_make(&ll, sizeof(uint32_t));

    assert(linked_list_count(&ll) == 0);
    for (uint32_t i = 0; i < 10; i++) {

      linked_list_push_front(&ll, &i);
    }
    assert(linked_list_count(&ll) == 10);

    for (uint32_t i = 0; i < 10; i++) {
      assert(i ==
             *(uint32_t *)linked_list_get(
                 &ll, 9 - i));
    }

    linked_list_destroy(&ll);
    print_green("done!\n");
  }
  {
    print_test_name(
        "linked_list_push_back, ");
    linked_list ll;
    linked_list_make(&ll, sizeof(uint32_t));

    assert(linked_list_count(&ll) == 0);
    linked_list_push_back(&ll,
                          &(uint32_t){10});
    assert(linked_list_count(&ll) == 1);

    assert(
        10 ==
        *(uint32_t *)linked_list_head(&ll));
    assert(
        10 ==
        *(uint32_t *)linked_list_tail(&ll));
    assert(10 ==
           *(uint32_t *)linked_list_get(&ll,
                                        0));

    linked_list_destroy(&ll);
    print_green("done!\n");
  }
  {
    print_test_name(
        "linked_list_push_back many, ");
    linked_list ll;
    linked_list_make(&ll, sizeof(uint32_t));

    assert(linked_list_count(&ll) == 0);
    for (uint32_t i = 0; i < 10; i++) {

      linked_list_push_back(&ll, &i);
    }
    assert(linked_list_count(&ll) == 10);

    for (uint32_t i = 0; i < 10; i++) {
      assert(i ==
             *(uint32_t *)linked_list_get(
                 &ll, i));
    }

    linked_list_destroy(&ll);
    print_green("done!\n");
  }
  {
    print_test_name(
        "linked_list_push front, ");
    linked_list ll;
    linked_list_make(&ll, sizeof(uint32_t));

    assert(linked_list_count(&ll) == 0);
    for (uint32_t i = 0; i < 10; i++) {

      linked_list_push_back(&ll, &i);
    }
    assert(linked_list_count(&ll) == 10);

    linked_list_push(&ll, &(uint32_t){100},
                     0);
    assert(linked_list_count(&ll) == 11);

    for (uint32_t i = 1; i < 11; i++) {
      assert(i - 1 ==
             *(uint32_t *)linked_list_get(
                 &ll, i));
    }
    assert(100 ==
           *(uint32_t *)linked_list_get(&ll,
                                        0));

    linked_list_destroy(&ll);
    print_green("done!\n");
  }
  {
    print_test_name(
        "linked_list_push before last, ");
    linked_list ll;
    linked_list_make(&ll, sizeof(uint32_t));

    assert(linked_list_count(&ll) == 0);
    for (uint32_t i = 0; i < 10; i++) {

      linked_list_push_back(&ll, &i);
    }
    assert(linked_list_count(&ll) == 10);

    linked_list_push(&ll, &(uint32_t){100},
                     9);
    assert(linked_list_count(&ll) == 11);

    for (uint32_t i = 0; i < 9; i++) {
      assert(i ==
             *(uint32_t *)linked_list_get(
                 &ll, i));
    }
    assert(100 ==
           *(uint32_t *)linked_list_get(&ll,
                                        9));
    assert(9 == *(uint32_t *)linked_list_get(
                    &ll, 10));

    linked_list_destroy(&ll);
    print_green("done!\n");
  }
  {
    print_test_name(
        "linked_list_push after first, ");
    linked_list ll;
    linked_list_make(&ll, sizeof(uint32_t));

    assert(linked_list_count(&ll) == 0);
    for (uint32_t i = 0; i < 10; i++) {
      linked_list_push_back(&ll, &i);
    }
    assert(linked_list_count(&ll) == 10);

    linked_list_push(&ll, &(uint32_t){100},
                     1);
    assert(linked_list_count(&ll) == 11);

    for (uint32_t i = 2; i < 10; i++) {
      assert(i - 1 ==
             *(uint32_t *)linked_list_get(
                 &ll, i));
    }
    assert(100 ==
           *(uint32_t *)linked_list_get(&ll,
                                        1));
    assert(0 == *(uint32_t *)linked_list_get(
                    &ll, 0));

    linked_list_destroy(&ll);
    print_green("\033[32mdone!\033[31m\n");
  }
  {
    print_test_name(
        "linked_list_push middle, ");
    linked_list ll;
    linked_list_make(&ll, sizeof(uint32_t));

    assert(linked_list_count(&ll) == 0);
    for (uint32_t i = 0; i < 10; i++) {

      linked_list_push_back(&ll, &i);
    }
    assert(linked_list_count(&ll) == 10);

    linked_list_push(&ll, &(uint32_t){100},
                     4);

    assert(linked_list_count(&ll) == 11);

    for (uint32_t i = 0; i < 4; i++) {
      assert(i ==
             *(uint32_t *)linked_list_get(
                 &ll, i));
    }
    assert(100 ==
           *(uint32_t *)linked_list_get(&ll,
                                        4));
    for (uint32_t i = 5; i < 11; i++) {
      assert(i - 1 ==
             *(uint32_t *)linked_list_get(
                 &ll, i));
    }

    linked_list_destroy(&ll);
    print_green("done!\n");
  }

  printf("done testing "
         "collections/test_array_dyn.c\n");

  return 0;
}
