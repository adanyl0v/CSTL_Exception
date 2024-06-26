if(.. STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and run \"cmake -S ${CMAKE_SOURCE_DIR} -B .\" from there")
endif()

cmake_minimum_required(VERSION 3.5)
project(CSTL_Exception VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

message(STATUS "* CMake build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "* Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "* Current binary dir: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "* Current list dir: ${CMAKE_CURRENT_LIST_DIR}")

set(CSTL_EXCEPTION_PUBLIC_HEADERS
    "include/BeginCode.h"
    "include/Exception.h"
)

add_library(CSTL_Exception SHARED
    "src/Exception.c"
)

set_target_properties(CSTL_Exception PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
)

set(CSTL_EXCEPTION_INSTALL_INCLUDE_DIR "include/${CMAKE_PROJECT_NAME}")
target_include_directories(CSTL_Exception
    PUBLIC
    $<BUILD_INTERFACE:${CSTL_Exception_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CSTL_EXCEPTION_INSTALL_INCLUDE_DIR}>
)

set(CSTL_EXCEPTION_INSTALL_LIBRARY_DIR "lib")
set(CSTL_EXCEPTION_INSTALL_BINARY_DIR "bin")
install(
    TARGETS CSTL_Exception
    EXPORT ${CMAKE_PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CSTL_EXCEPTION_INSTALL_LIBRARY_DIR}
    LIBRARY DESTINATION ${CSTL_EXCEPTION_INSTALL_LIBRARY_DIR}
    RUNTIME DESTINATION ${CSTL_EXCEPTION_INSTALL_BINARY_DIR}
)

install(
    FILES ${CSTL_EXCEPTION_PUBLIC_HEADERS}
    DESTINATION ${CSTL_EXCEPTION_INSTALL_INCLUDE_DIR}
)

set(config_version_file "${CMAKE_CURRENT_LIST_DIR}/modules/cmake/${CMAKE_PROJECT_NAME}ConfigVersion.cmake")
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${config_version_file}
    VERSION ${CSTL_Exception_VERSION}
    COMPATIBILITY SameMajorVersion
)

export(
    EXPORT ${CMAKE_PROJECT_NAME}Targets
    FILE "${CMAKE_CURRENT_LIST_DIR}/modules/cmake/${CMAKE_PROJECT_NAME}Targets.cmake"
)

set(config_file "${CMAKE_CURRENT_LIST_DIR}/modules/cmake/${CMAKE_PROJECT_NAME}Config.cmake")
configure_package_config_file(
    "res/cmake/${CMAKE_PROJECT_NAME}Config.cmake.in"
    ${config_file}
    INSTALL_DESTINATION "${CMAKE_CURRENT_LIST_DIR}/modules/cmake"
)

set(CSTL_EXCEPTION_INSTALL_CONFIG_DIR "${CSTL_EXCEPTION_INSTALL_LIBRARY_DIR}/cmake/${CMAKE_PROJECT_NAME}")
install(
    EXPORT ${CMAKE_PROJECT_NAME}Targets
    FILE ${CMAKE_PROJECT_NAME}Targets.cmake
    NAMESPACE ${CMAKE_PROJECT_NAME}::
    DESTINATION ${CSTL_EXCEPTION_INSTALL_CONFIG_DIR}
)

set(install_config_file "${PROJECT_BINARY_DIR}/CMakeFiles/${CMAKE_PROJECT_NAME}Config.cmake")
configure_package_config_file(
    "res/cmake/${CMAKE_PROJECT_NAME}Config.cmake.in"
    ${install_config_file}
    INSTALL_DESTINATION ${CSTL_EXCEPTION_INSTALL_CONFIG_DIR}
)

install(
    FILES ${config_version_file} ${install_config_file}
    DESTINATION "${CSTL_EXCEPTION_INSTALL_CONFIG_DIR}"
)
