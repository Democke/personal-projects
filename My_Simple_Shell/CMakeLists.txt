cmake_minimum_required(VERSION 3.3)
project(My_Simple_Shell)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCE_FILES
    alias/alias.c
    alias/alias.h
    history/history.c
    history/history.h
    linkedlist/genericData.h
    linkedlist/linkedList.c
    linkedlist/linkedList.h
    linkedlist/listUtils.c
    linkedlist/listUtils.h
    pipes/pipes.c
    pipes/pipes.h
    process/process.c
    process/process.h
    shell/shell.c
    shell/shell.h
    tokenize/makeArgs.c
    tokenize/makeArgs.h
    utils/myUtils.c
    utils/myUtils.h
    msshmain.c
    string_edit/string_edit.c
    string_edit/string_edit.h)

add_executable(My_Simple_Shell ${SOURCE_FILES})
