cmake_minimum_required(VERSION 3.6)

project(NavUI
	DESCRIPTION "A Linux GTK program to display NMEA data in a useful way"
	LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

# gcc $(pkg-config --cflags gtk+-3.0) -o hello-world-gtk main.cpp $(pkg-config --libs gtk+-3.0) -lrt -lm -lpthread

set (CMAKE_CXX_FLAGS "-g -Wall -Winvalid-pch -Wnon-virtual-dtor -Wextra -Wno-unused-parameter")

find_package(PkgConfig)

pkg_check_modules(GTK30 REQUIRED IMPORTED_TARGET gtk+-3.0)
message(STATUS "gtk+-3.0 library found:")
message(STATUS "    version: ${GTK30_VERSION}")
message(STATUS "    libraries: ${GTK30_LINK_LIBRARIES}")
message(STATUS "    include path: ${GTK30_INCLUDE_DIRS}")

include_directories(${CMAKE_SOURCE_DIR} ${GTK30_INCLUDE_DIRS})

add_executable(NavUI src/main.cpp)

target_link_libraries(NavUI PkgConfig::GTK30)
target_link_libraries(NavUI rt)
target_link_libraries(NavUI m)
target_link_libraries(NavUI pthread)
