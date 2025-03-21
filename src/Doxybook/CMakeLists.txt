cmake_minimum_required(VERSION 3.21)
project(Doxybook2)

# Dependencies
if(NOT USE_CPM)
  find_package(inja CONFIG REQUIRED)
  find_package(fmt CONFIG REQUIRED)
  find_package(nlohmann_json CONFIG REQUIRED)
  find_package(spdlog CONFIG REQUIRED)

  if(MSVC)
    find_package(Dirent REQUIRED)
  endif()
endif()

# Project source files
set(DOXYDOWN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${DOXYDOWN_INCLUDE_DIR}/Doxybook/*.hpp)

# Add the project source files
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "doxybook2")
target_include_directories(${PROJECT_NAME} PUBLIC ${DOXYDOWN_INCLUDE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# Definitions
if(MSVC)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)

  # See issue there: https://github.com/actions/runner-images/issues/10004#issuecomment-2156109231
  # and there: https://github.com/gabime/spdlog/issues/3119#issuecomment-2218733127
  target_compile_definitions(${PROJECT_NAME} PRIVATE _DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR)
endif()

# Install
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../include
  DESTINATION . FILES_MATCHING PATTERN "*.hpp"
)

# Libraries
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt fmt::fmt-header-only spdlog::spdlog_header_only pantor::inja nlohmann_json nlohmann_json::nlohmann_json)

if(MSVC)
  target_link_libraries(${PROJECT_NAME} PRIVATE Dirent)
endif()
