cmake_minimum_required(VERSION 3.16)
project(embedded_runtime_reference C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
  set(REF_WARNING_FLAGS /W4 /WX)
else()
  set(REF_WARNING_FLAGS -Wall -Wextra -Werror -pedantic)
endif()

add_library(ref_runtime STATIC src/ref_runtime.c)
target_include_directories(ref_runtime PUBLIC include)
target_compile_options(ref_runtime PRIVATE ${REF_WARNING_FLAGS})

add_executable(reference_tests tests/test_reference.c)
target_link_libraries(reference_tests PRIVATE ref_runtime)
target_compile_options(reference_tests PRIVATE ${REF_WARNING_FLAGS})

enable_testing()
add_test(NAME reference_tests COMMAND reference_tests)

add_executable(host_experiment experiments/host_experiment.c)
target_link_libraries(host_experiment PRIVATE ref_runtime)
target_compile_options(host_experiment PRIVATE ${REF_WARNING_FLAGS})

find_package(Python3 COMPONENTS Interpreter QUIET)
if(Python3_Interpreter_FOUND)
  add_test(
    NAME host_experiment_replay
    COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/experiments/run_host_experiment.py
            --check
  )
endif()

add_subdirectory(virtual)
