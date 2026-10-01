add_library(virtual_system STATIC src/virtual_system.c)
target_include_directories(virtual_system PUBLIC include ../include)
target_link_libraries(virtual_system PUBLIC ref_runtime)
target_compile_options(virtual_system PRIVATE ${REF_WARNING_FLAGS})

add_executable(virtual_system_tests tests/test_virtual_system.c)
target_link_libraries(virtual_system_tests PRIVATE virtual_system ref_runtime)
target_compile_options(virtual_system_tests PRIVATE ${REF_WARNING_FLAGS})

add_test(NAME virtual_system_tests COMMAND virtual_system_tests)
