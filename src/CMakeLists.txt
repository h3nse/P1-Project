add_library(functions mainfuncs.c
        cpp.c
        cpp.c
        cpp.c
        cpp.h)
target_include_directories(functions PUBLIC .)

add_executable(main main.c
        cpp.c)
target_link_libraries(main functions)

