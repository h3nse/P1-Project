
add_executable(test_functions test_functions.c)
target_link_libraries(test_functions PRIVATE project)

add_test(NAME function_test COMMAND test_functions)