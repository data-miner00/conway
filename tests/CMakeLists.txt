# Tests are built with warnings and sanitizers on, so memory bugs (reading past the end of an
# array, forgetting to free) make the test fail instead of going unnoticed.
add_compile_options(-Wall -Wextra -g -fsanitize=address,undefined -fno-sanitize-recover=all)
add_link_options(-fsanitize=address,undefined)

add_executable(
  test_life

  test_life.c
  ${CMAKE_SOURCE_DIR}/src/life.c
)

target_include_directories(
  test_life
  PRIVATE ${CMAKE_SOURCE_DIR}/src
)

add_test(NAME test_life COMMAND test_life)
