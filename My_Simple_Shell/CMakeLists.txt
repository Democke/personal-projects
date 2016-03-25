cmake_minimum_required(VERSION 3.3)
project(Lab8)

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
    linkedlist/requiredIncludes.h
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
    cscd340hw8.c
        string_edit/string_edit.c
        string_edit/string_edit.h)

add_executable(Lab8 ${SOURCE_FILES})
