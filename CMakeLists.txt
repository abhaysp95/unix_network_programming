cmake_minimum_required(VERSION 3.15...3.20)

project(Unix_Network_Programming LANGUAGES C)


SET(CMAKE_C_STANDARD 99)
SET(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-Wall")

set(CMAKE_C_FLAGS_DEBUG "-ggdb")
set(CMAKE_C_FLAGS_RELEASE "-03")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(LIB_SOURCES
  unp_lib/src/error.c)
set(LIB_HEADERES
	unp_lib/inc/config.h
  unp_lib/inc/unp.h)

add_library(unp_library STATIC "${LIB_SOURCES}" "${LIB_HEADERES}")

target_include_directories(unp_library PUBLIC unp_lib/inc)

# target_compile_features(apue_library PUBLIC c_std_99)

add_subdirectory(introduction)
