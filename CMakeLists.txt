############################################################
#   base
############################################################

cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
set(CMAKE_SUPPRESS_REGENERATION TRUE)

############################################################
#   setting Project informations
############################################################

set(PROJECT_NAME example)
project(${PROJECT_NAME})

################################################################################
# Include useful CMake functions
################################################################################
include(GNUInstallDirs)
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckFunctionExists)
include(CheckPrototypeDefinition)

################################################################################
# Find LLVM
################################################################################
include(${CMAKE_SOURCE_DIR}/cmake/find_llvm.cmake)
set(NEEDED_LLVM_VARS
  LLVM_PACKAGE_VERSION
  LLVM_VERSION_MAJOR
  LLVM_VERSION_MINOR
  LLVM_VERSION_PATCH
  LLVM_DEFINITIONS
  LLVM_INCLUDE_DIRS
  LLVM_LIBRARY_DIRS
  LLVM_TOOLS_BINARY_DIR
  TARGET_TRIPLE
)
################################################################################
# Find Curses (Needed by LLVMSupport for some reason)
################################################################################
# find_package(Curses REQUIRED)
find_library(LLVM_TERMCAP_LIBRARY NAMES tinfo termcap ncursesw ncurses cursesw curses)

############################################################
#   generate makefiles
############################################################


message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Found LLVM include ${LLVM_INCLUDE_DIRS}")
message(STATUS "Found LLVM lib ${LLVM_LIBRARY_DIRS}")

include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(${PROJECT_NAME} main.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  foreach(link_lib IN LISTS LIBRARY_LIST)
    target_link_libraries(${PROJECT_NAME} optimized ${link_lib})
    target_link_libraries(${PROJECT_NAME} debug     ${link_lib}d)
  endforeach()
else()
  target_link_libraries(${PROJECT_NAME} ${LIBRARY_LIST})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-unused-parameter -fno-strict-aliasing -fno-exceptions")
endif()

target_link_libraries(${PROJECT_NAME}
  LLVMTransformUtils
  LLVMAnalysis
  LLVMTarget
  LLVMOption
  LLVMIRReader
  LLVMObject
  LLVMCore
  LLVMSupport
  LLVMAsmParser
  LLVMDemangle
  LLVMBitReader
  LLVMBinaryFormat
  ${LLVM_TERMCAP_LIBRARY}
)

message(STATUS "    = ${llvm_libs}")
