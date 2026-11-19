add_library(project STATIC 
        project.c
        cpp.c
        ej-dcpp.c)

target_include_directories(project PUBLIC .)

add_executable(main main.c)

target_link_libraries(main PRIVATE project)

