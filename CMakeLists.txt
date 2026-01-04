cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version.h"
)

# --- Определение целей (библиотека и исполняемый файл) ---
add_library(ip_filter_lib src/lib.cpp)
add_executable(ip_filter src/main.cpp)

# Устанавливаем стандарт C++
set_target_properties(ip_filter ip_filter_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_BINARY_DIR}"
)
target_include_directories(ip_filter_lib PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE ip_filter_lib)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT "dm.lyrae@ya.ru")
include(CPack)

enable_testing()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/tests")
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/tests")
endif()

add_test(
    NAME version_check_test
    COMMAND bash ${CMAKE_SOURCE_DIR}/tests/test_1.sh $<TARGET_FILE:ip_filter> ${PROJECT_VERSION}
)

add_test(
    NAME ip_filter_functionality_test
    COMMAND bash ${CMAKE_SOURCE_DIR}/tests/test_2.sh $<TARGET_FILE:ip_filter>
)