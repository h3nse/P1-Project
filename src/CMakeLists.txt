add_library(project STATIC
        project.c
        graphGenerator.c
        cpp.c
        graphGenerator.c
        ej-dcpp.c
        graph_visualization.c)


target_include_directories(project PUBLIC .)

add_executable(main main.c)

target_link_libraries(main PRIVATE project)

