cmake_minimum_required(VERSION 3.9)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(ip_filter VERSION 0.0.1)
endif()

set(SRC_DIR "./src")
set(BIN_INC_DIR "${PROJECT_BINARY_DIR}/src")


configure_file("${PROJECT_SOURCE_DIR}/${SRC_DIR}/version.h.in" "${PROJECT_BINARY_DIR}/${SRC_DIR}/version.h")
configure_file("${PROJECT_SOURCE_DIR}/${SRC_DIR}/ip_filter.tsv" "${PROJECT_BINARY_DIR}/ip_filter.tsv" COPYONLY)
set(SOURCE_FILES main.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})


set_target_properties(${CMAKE_PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
       )


include_directories(${SRC_DIR} ${BIN_INC_DIR})

set(IP_FILTER_LIB ip_filter_lib)

add_subdirectory(${SRC_DIR})
add_subdirectory(tests)

target_link_libraries(${CMAKE_PROJECT_NAME} ${IP_FILTER_LIB})


install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT srgmatveev@gmail.com)

include (CPack)

enable_testing()

add_test(gtest_valid_version ./tests/unit_tests/Unit_Tests_run)


# Doxygen Build
option(BUILD_DOC "Build Documentation" ON)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR ${CMAKE_CURRENT_BINARY_DIR}/build/docs)
    if(NOT EXISTS ${BUILD_DOC_DIR})
        file(MAKE_DIRECTORY ${BUILD_DOC_DIR})
    endif()

    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    message("Doxygen buld started")
    add_custom_target(Doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)