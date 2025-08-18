#### cmake

- basic run:

```bash
cmake -S . -B _build
cmake --build _build enable_linux=ON

```

- outputs is in ./\_bin/

#### ./cmake

- main.cmake is the entry point.
- it includes all other .cmake files.
- config.cmake is included last as that is the only one that runs code, others are just functions.
