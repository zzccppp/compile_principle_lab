cmake_minimum_required(VERSION 3.21)
project(lab1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1) 

add_custom_command(
  OUTPUT ../lex.yy.c
  COMMAND flex --header=lex.yy.h cmm.l
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

aux_source_directory(. SRC)

add_executable(lab1 ${SRC})
