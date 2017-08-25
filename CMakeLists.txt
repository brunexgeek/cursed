cmake_minimum_required(VERSION 2.8)

project(cursed)


set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -std=gnu99 -Wl,--no-undefined -fPIC -Wall -Wextra -Wconversion -Werror=return-type -Werror=implicit-function-declaration")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wl,--no-undefined -fPIC -Wall -Wextra -Wconversion -Werror=return-type -Werror=implicit-function-declaration")
set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS_RELEASE} -s -O3")
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -s -O3")
set(CMAKE_C_FLAGS_DEBUG  "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")


add_subdirectory(lib)