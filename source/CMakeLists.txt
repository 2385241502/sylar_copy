cmake_minimum_required(VERSION 2.8)
project(sylar)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -o3 -g -std=c++11 -Wall -Wno-depencated -Werror -Wno-unused-function")

set(LIB_SRC
    sylar/log.cc
    )

add_library(sylar SHARED ${LIB_SRC})
#add_library(syalr_static STATIC ${LIB_SRC})
#SET_TABGET_PROPERTIES (sylar_static PROPERTIES OUTPUT_NAME "sylar")

add_executable(test tests/test.cc)
add_dependencies(test sylar)
target_link_libraries(test sylar)

SET(EXECUTEABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
