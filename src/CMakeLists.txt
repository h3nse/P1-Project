add_library(functions mainfuncs.c
        cpp.c
        cpp.c
        cpp.c
        cpp.h
        ej-dccp.c)
target_include_directories(functions PUBLIC .)

add_executable(main main.c
        cpp.c)
add_executable(ej-dccp ej-dccp.c
        ej-dccp.h)
target_link_libraries(main functions)

