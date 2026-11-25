cmake_minimum_required(VERSION 3.14)
project(P1 C)
set(CMAKE_C_STANDARD 11)

#add graphviz library

set(GRAPHVIZ_DIR "C:/Program Files/Graphviz")


find_path(GRAPHVIZ_INCLUDE_DIR NAMES gvc.h
        HINTS "${GRAPHVIZ_DIR}/include/graphviz" "${GRAPHVIZ_DIR}/include"
)
find_library(GVC_LIB NAMES gvc libgvc
        HINTS "${GRAPHVIZ_DIR}/lib"
)
find_library(CGRAPH_LIB NAMES cgraph libcgraph
        HINTS "${GRAPHVIZ_DIR}/lib"
)

include_directories(${GRAPHVIZ_INCLUDE_DIR})

#viewing pngs in clion
find_package(PNG)
include_directories(${PNG_INCLUDE_DIRS})


add_subdirectory(src)
enable_testing()
add_subdirectory(test)


