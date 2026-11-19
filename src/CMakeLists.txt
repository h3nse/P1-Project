add_library(functions project.c
        cpp.c
        ej-dcpp.c)
target_include_directories(functions PUBLIC .)

add_executable(main main.c
        cpp.c)
add_executable(ej-dccp ej-dcpp.c
        ej-dcpp.h)
target_link_libraries(main functions)

