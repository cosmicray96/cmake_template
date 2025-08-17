#include <stdio.h>

#include <dyn_main/dyn_main.h>
#include <main/collections/str_ascii.h>

#include "use_main/fea/common_file.h"

int main() {

  str_ascii str = str_ascii_make("Hello, World!");

  printf("%s", str_ascii_get_ptr(&str));

  str_ascii_destroy(&str);

  printf("process id form unistd.h: %d\n", func1());

  dyn_main_func();

  return 0;
}
