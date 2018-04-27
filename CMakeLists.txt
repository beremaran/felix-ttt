cmake_minimum_required(VERSION 3.10)
project(felix_ttt C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

set(SOURCE_COMMON
        game/board.c
        game/board.h
        engine/tree.c
        engine/tree.h
        game/state.c
        game/state.h
        engine/mcts.c
        engine/mcts.h
        engine/random.c
        engine/random.h
        game/history.c
        game/history.h
        tgf/tgf.c
        tgf/tgf.h
        utils/mt19937.c
        utils/mt19937.h
        utils/binarysearch.c
        utils/binarysearch.h)

set(SOURCE_CLI
        main.c
        main.h
        interface/ttp.c
        interface/ttp.h
        interface/ascii.c
        interface/ascii.h
        ${SOURCE_COMMON})

set(SOURCE_GUI
        interface/gui.c
        interface/gui.h
        ${SOURCE_COMMON})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(felix_ttt ${SOURCE_CLI})
add_executable(felix_ttt_gui ${SOURCE_GUI})
target_link_libraries(felix_ttt m)

target_link_libraries(felix_ttt_gui m pthread ${GTK3_LIBRARIES})