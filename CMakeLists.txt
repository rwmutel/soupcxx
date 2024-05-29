cmake_minimum_required(VERSION 3.15)

set(
	PROJECT_NAME soupcxx
	VERSION 0.1
	DESCRIPTION "a simple C++ library for parsing and operating HTML and MD documents"
)
set(CTEST_BUILD_NAME soupcxx_test)
project(${PROJECT_NAME} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

set(WARNINGS_AS_ERRORS OFF)

set(ENABLE_PVS_STUDIO OFF)

#! UndefinedBehaviorSanitizer (UBSan).
#  Info: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
set(ENABLE_UBSan OFF)
#! AddressSanitizer -- detects use after free or after scope exit,
#  memory overflows and leaks.
#  Info: https://github.com/google/sanitizers/wiki/AddressSanitizer
set(ENABLE_ASAN OFF)
#! ThreadSanitizer -- detects data races.
#  Info: https://clang.llvm.org/docs/ThreadSanitizer.html
set(ENABLE_TSan OFF)
#! MemorySanitizer -- detects uninitialized memory reads
#  Info: https://github.com/google/sanitizers/wiki/MemorySanitizer
set(ENABLE_MSAN OFF)

#! Be default -- build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

# Warnings as errors should be imported here -- do not move this line
include(cmake/CompilerWarnings.cmake)

##########################################################
# Project files, packages, libraries and so on
##########################################################

#! Project main executable source compilation

add_library(soupcxx
		SHARED
		include/Nodes/Node.h
		include/Nodes/Tag.h
		include/Soups/Soup.h
		include/utils.h
		include/Soups/HTMLSoup.h
		include/Soups/HTMLSoup.h
		src/Soups/HTMLSoup.cpp
		api/soupcxx.h
		src/Nodes/Tag.cpp
		src/Nodes/Text.cpp
		include/Nodes/Text.h
)

target_include_directories(
		soupcxx
		PUBLIC
		include
		include/Nodes
		include/Soups
)

add_executable(working_demo demo.cpp)
target_link_libraries(working_demo soupcxx)
target_include_directories(working_demo PRIVATE api)

add_executable(${CTEST_BUILD_NAME} tests.cpp
		api/soupcxx.h)
target_link_libraries(${CTEST_BUILD_NAME} soupcxx)
target_include_directories(${CTEST_BUILD_NAME} PRIVATE api)

#! Add external packages
# gtest
include(FetchContent)
FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG        f8d7d77c06936315286eb55f8de22cd23c188571 # release-1.14.0
		DOWNLOAD_EXTRACT_TIMESTAMP True
)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(${CTEST_BUILD_NAME} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${CTEST_BUILD_NAME})

#INSTALL(PROGRAMS
#		$<TARGET_FILE:${PROJECT_NAME}> # ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
#		DESTINATION bin)

# Define ALL_TARGETS variable to use in PVS and Sanitizers
set(ALL_TARGETS ${PROJECT_NAME} ${CTEST_BUILD_NAME} working_demo)

# Include CMake setup
include(cmake/main-config.cmake)
