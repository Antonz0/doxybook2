cmake_minimum_required(VERSION 3.21)
project(Doxybook2Tests)

# Dependencies
find_package(Catch2 CONFIG REQUIRED)

# Project source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# Add the project source files
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/Doxybook)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if(DOXYBOOK_STATIC_STDLIB)
  target_link_libraries(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()

# Definitions
if(MSVC)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)

  # See issue there: https://github.com/actions/runner-images/issues/10004#issuecomment-2156109231
  # and there: https://github.com/gabime/spdlog/issues/3119#issuecomment-2218733127
  target_compile_definitions(${PROJECT_NAME} PRIVATE _DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR)
endif()

# Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Doxybook2 Catch2::Catch2)

# Testing
enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PRIVATE IMPORT_DIR="${CMAKE_SOURCE_DIR}/example/doxygen/xml")
