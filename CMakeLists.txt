cmake_minimum_required(VERSION 3.5)

project("p5-slaughterhouse" LANGUAGES "CXX")

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    enable_testing()
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")

include("${PROJECT_SOURCE_DIR}/cmake/utils.cmake")
include("${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake")

unset("_target")
set("_target" "${PROJECT_NAME}")
mark_as_advanced("_target")

add_library("${_target}" MODULE)

file(
    GLOB_RECURSE "_sources"
    LIST_DIRECTORIES FALSE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)
mark_as_advanced("_sources")
target_sources("${_target}" PRIVATE ${_sources})

target_compile_features("${_target}" PRIVATE "cxx_std_20")

set_target_properties("${_target}" PROPERTIES
    PREFIX ""
    OUTPUT_NAME "${PROJECT_NAME}"
    CXX_STANDARD "20"
    CXX_STANDARD_REQUIRED TRUE
    DEFINE_SYMBOL "P5_SLAUGHTERHOUSE_IMPLEMENTATION"
    C_VISIBILITY_PRESET "hidden"
    CXX_VISIBILITY_PRESET "hidden"
    VISIBILITY_INLINES_HIDDEN TRUE
    POSITION_INDEPENDENT_CODE TRUE
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/.output/addons/metamod/plugins"
)

if(MSVC)
    if(SIZE_OF_VOID_P EQUAL 4)
        target_compile_options("${_target}" PRIVATE "/arch:sse" "/arch:sse2")
    endif(SIZE_OF_VOID_P EQUAL 4)
else(MSVC)
    target_compile_options("${_target}" PRIVATE "-mtune=generic" "-msse" "-msse2")
    target_link_options("${_target}" PRIVATE "-static-libgcc")
    target_link_options("${_target}" PRIVATE "-static-libstdc++")
    target_link_options("${_target}" PRIVATE "-Wl,--no-undefined")
endif(MSVC)

cmake_language(CALL "_utils::get_version" "_version")
cmake_language(CALL "_utils::get_timestamp" "_timestamp")
mark_as_advanced("_version")
mark_as_advanced("_timestamp")

target_compile_definitions(
    "${_target}" PRIVATE
    "P5_SLAUGHTERHOUSE_PLUGIN_NAME=\"${PROJECT_NAME}\""
    "P5_SLAUGHTERHOUSE_PLUGIN_VERSION=\"${_version}\""
    "P5_SLAUGHTERHOUSE_PLUGIN_TIMESTAMP=\"${_timestamp}\""
)

target_link_libraries(
    "${_target}" PRIVATE
    "p5-lambda"
    "Boost::boost"
)
