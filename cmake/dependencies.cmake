cmake_minimum_required(VERSION 3.5)

include("${CMAKE_CURRENT_LIST_DIR}/utils/include_all.cmake")
cmake_language(CALL "_utils::include_all" "${CMAKE_CURRENT_LIST_DIR}/dependencies")
