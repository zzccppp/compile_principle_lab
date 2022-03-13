cmake_minimum_required(VERSION 3.21)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

add_custom_command(
  OUTPUT ../lex.yy.c
  COMMAND flex cmm.l
  DEPENDS cmm.l
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_command(
  OUTPUT ../cmm.tab.c
  OUTPUT ../cmm.tab.h
  COMMAND bison -d -Wcounterexamples cmm.y
  DEPENDS cmm.y
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(lab1 lex.yy.c cmm.tab.c main.c)
