cmake_minimum_required(VERSION 3.21)
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_LIST_DIR}/modules"
)

project(Doxybook2)

if(USE_CPM)
  include(cmake/CPM.cmake)

  CPMAddPackage(
    NAME Catch2
    GITHUB_REPOSITORY catchorg/Catch2
    VERSION 2.13.6
    OPTIONS
      "CATCH_BUILD_TESTING OFF"
      "CATCH_BUILD_EXAMPLES OFF"
      "CATCH_BUILD_EXTRA_TESTS OFF"
      "CATCH_BUILD_FUZZERS OFF")
  CPMAddPackage("gh:fmtlib/fmt#8.0.1")
  CPMAddPackage("gh:pantor/inja#v3.3.0")
  CPMAddPackage(
    NAME nlohmann_json
    GITHUB_REPOSITORY nlohmann/json
    VERSION 3.9.1
    OPTIONS
      "JSON_BuildTests OFF"
  )
  CPMAddPackage("gh:gabime/spdlog#v1.9.1")
  CPMAddPackage("gh:jarro2783/cxxopts#v2.2.1")

  if(MSVC)
    CPMAddPackage("gh:tronkko/dirent#1.23.2")
  endif()
endif()

if(APPLE OR MSVC OR CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(DOXYBOOK_STATIC_STDLIB OFF)
else()
  option(DOXYBOOK_STATIC_STDLIB "Use static stdlib" ON)
endif()

option(DOXYBOOK_TESTS "Build Doxybook2 tests" OFF)

set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Select build type")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/Doxybook)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/DoxybookCli)

if(DOXYBOOK_TESTS)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/DoxybookTests)
endif()
