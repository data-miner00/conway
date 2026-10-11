cmake_minimum_required(VERSION 3.13)

project(
  Conway

  VERSION 1.0.0.0
  DESCRIPTION "Trying to do a conway game"
  LANGUAGES C
)

set(AUTHOR_NAME shaun)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(
  # Name of executable. Using project name.
  ${PROJECT_NAME}

  # Source of executable
  src/main.c
  src/life.c
)

find_package(Curses REQUIRED)

add_executable(
  # ncurses frontend
  ${PROJECT_NAME}Ncurses

  src/main_ncurses.c
  src/life.c
)

target_include_directories(
  ${PROJECT_NAME}Ncurses
  PRIVATE ${CURSES_INCLUDE_DIR}
)

target_link_libraries(
  ${PROJECT_NAME}Ncurses
  ${CURSES_LIBRARIES}
)

enable_testing()
add_subdirectory(tests)

