cmake_minimum_required(VERSION 2.8.12)
project(cpp_full)
set(CMAKE_VERBOSE_MAKEFILE on)


set(CMAKE_CXX_STANDARD 17)
include_directories (/Users/miguel/anaconda/envs/py36/include/)
include_directories (emsdk/upstream/emscripten/system/include/)
include_directories (/usr/local/Cellar/boost/1.69.0_2/include/)
include_directories (/Users/miguel/anaconda/include)

file(GLOB_RECURSE CORE_HDR src/*.hpp)
file(GLOB_RECURSE CORE_SRC src/*.cpp)

#
# Trying usual cmake project compiler execution
#

add_executable(cpp_full ${CORE_SRC} ${CORE_HDR})

set_target_properties(cpp_full PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 --bind")
