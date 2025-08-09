#include "main/collections/str_ascii.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

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
    str_ascii str = str_ascii_make(NULL);
    assert(str_ascii_count(&str) == 0);
    str_ascii_destroy(&str);
    print_green("done!\n");
  }
  {
    print_test_name("make with value, ");
    str_ascii str = str_ascii_make("Hello!");
    str_ascii_destroy(&str);
    print_green("done!\n");
  }
  {
    print_test_name("get value, ");
    str_ascii str = str_ascii_make("Hello!");

    char *value = str_ascii_get_ptr(&str);
    assert(strcmp(value, "Hello!") == 0);

    str_ascii_destroy(&str);
    print_green("done!\n");
  }
  {
    print_test_name("count, ");
    str_ascii str = str_ascii_make("Hello!");

    assert(str_ascii_count(&str) == 6);

    str_ascii_destroy(&str);
    print_green("done!\n");
  }
  {
    print_test_name("at, ");
    str_ascii str = str_ascii_make("Hello!");

    assert(str_ascii_at(&str, 0) == 'H');
    assert(str_ascii_at(&str, 1) == 'e');
    assert(str_ascii_at(&str, 2) == 'l');
    assert(str_ascii_at(&str, 3) == 'l');
    assert(str_ascii_at(&str, 4) == 'o');
    assert(str_ascii_at(&str, 5) == '!');
    assert(str_ascii_at(&str, 6) == '\0');

    str_ascii_destroy(&str);
    print_green("done!\n");
  }
  {
    print_test_name("join, ");
    str_ascii str1 =
        str_ascii_make("Hello!");
    str_ascii str2 =
        str_ascii_make("World!");

    str_ascii_join_back(
        &str1,
        str_ascii_span_make_whole(&str2));

    assert(str_ascii_count(&str1) == 12);

    assert(str_ascii_at(&str1, 0) == 'H');
    assert(str_ascii_at(&str1, 1) == 'e');
    assert(str_ascii_at(&str1, 2) == 'l');
    assert(str_ascii_at(&str1, 3) == 'l');
    assert(str_ascii_at(&str1, 4) == 'o');
    assert(str_ascii_at(&str1, 5) == '!');
    assert(str_ascii_at(&str1, 6) == 'W');
    assert(str_ascii_at(&str1, 7) == 'o');
    assert(str_ascii_at(&str1, 8) == 'r');
    assert(str_ascii_at(&str1, 9) == 'l');
    assert(str_ascii_at(&str1, 10) == 'd');
    assert(str_ascii_at(&str1, 11) == '!');
    assert(str_ascii_at(&str1, 12) == '\0');

    str_ascii_destroy(&str2);
    str_ascii_destroy(&str1);
    print_green("done!\n");
  }
  printf("done testing "
         "collections/test_array_dyn.c\n");
  return 0;
}
