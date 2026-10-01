add_library(virtual_system STATIC src/virtual_system.c src/virtual_scenarios.c)
target_include_directories(virtual_system PUBLIC include ../include)
target_link_libraries(virtual_system PUBLIC ref_runtime)
target_compile_options(virtual_system PRIVATE ${REF_WARNING_FLAGS})

add_executable(virtual_system_tests tests/test_virtual_system.c)
target_link_libraries(virtual_system_tests PRIVATE virtual_system ref_runtime)
target_compile_options(virtual_system_tests PRIVATE ${REF_WARNING_FLAGS})

add_executable(virtual_demo_cli src/virtual_demo_cli.c)
target_link_libraries(virtual_demo_cli PRIVATE virtual_system ref_runtime)
target_compile_options(virtual_demo_cli PRIVATE ${REF_WARNING_FLAGS})

add_test(NAME virtual_system_tests COMMAND virtual_system_tests)
add_test(NAME virtual_demo_test COMMAND virtual_demo_cli --verify)

find_package(Python3 COMPONENTS Interpreter QUIET)
if(Python3_Interpreter_FOUND)
  add_test(NAME virtual_ui_contracts_test
           COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/../demo/test_ui_contracts.py)
endif()
