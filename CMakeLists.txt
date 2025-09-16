cmake_minimum_required(VERSION 3.15...4.0.0)
project(ptools 
        VERSION 1.0        
        DESCRIPTION "tools for C projects"
        LANGUAGES C)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main)
set(DEPS ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
add_library(ptools STATIC ${SRC}/ptools_errors.c)
target_include_directories(ptools PUBLIC ${DEPS})
