cmake_minimum_required(VERSION 3.14)
project(P1 C)
set(CMAKE_C_STANDARD 11)

#add graphviz library

set(GRAPHVIZ_DIR "C:/Program Files/Graphviz")

#find_library(GRAPHLIB graphlib PATHS "C:/Program Files/Graphviz")

file(GLOB GVC_LIBS "${GRAPHVIZ_DIR}/lib/*.lib")
include_directories("${GRAPHVIZ_DIR}/include/graphviz")
link_directories("${GRAPHVIZ_DIR}/lib")

#find_package(graphviz QUIET)
#include(FetchContent)

#fetchcontent_declare(
#        graphviz
#        GIT_REPOSITORY "https://gitlab.com/graphviz/graphviz.git"
#        GIT_TAG "16.1.2"
#        GIT_PROGRESS TRUE
#)

#fetchcontent_makeavailable(graphviz)


add_subdirectory(src)
enable_testing()
add_subdirectory(test)


