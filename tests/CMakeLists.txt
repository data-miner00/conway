add_executable(
  test_hello

  test_hello.c
  ${CMAKE_SOURCE_DIR}/src/hello.c
)

target_include_directories(
  test_hello
  PRIVATE ${CMAKE_SOURCE_DIR}/src
)

add_test(NAME test_hello COMMAND test_hello)
