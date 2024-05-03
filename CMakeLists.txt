cmake_minimum_required(VERSION 3.13)
project(TorFS CXX)

set(CXX_STANDARD 23)

file(READ "VERSION" TORFS_VERSION)

add_definitions(-DTORFS_VERSION="${TORFS_VERSION}")

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)