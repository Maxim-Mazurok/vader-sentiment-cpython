g++ -std=c++17 -ggdb3 -O0 -pedantic-errors -Wall -Wextra \
  -fpie $(python3-config --cflags --embed) -o 'main.out' \
  'main.cpp' $(python3-config --embed --ldflags)