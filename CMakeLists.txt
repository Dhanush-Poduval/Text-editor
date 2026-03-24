cmake_minimum_required(VERSION 3.20.0)
add_library(
  text_editor
  STATIC
  src/memory.c
)
target_include_directories(
  text_editor
  PUBLIC
  ${CMAKE_SOURCE_DIR}/lib
)
project(donkey)

add_executable(
  editor
  src/main.c
)
target_link_directories (
  editor
  PRIVATE
  text_editor
)
