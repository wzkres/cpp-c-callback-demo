cmake_minimum_required(VERSION 3.17)
project(cpp_c_callback_demo)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)

file(GLOB_RECURSE c_sources CONFIGURE_DEPENDS "src/*.c")
file(GLOB_RECURSE cpp_sources CONFIGURE_DEPENDS "src/*.cpp")

set(exe_name cpp_c_callback_demo)

add_executable(${exe_name} ${c_sources} ${cpp_sources})
target_link_libraries (${exe_name} ${CMAKE_THREAD_LIBS_INIT})

enable_testing()
add_test(NAME test_run COMMAND ${exe_name})
