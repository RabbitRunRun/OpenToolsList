cmake_minimum_required(VERSION 2.7)
project(OTL)

option(OTL_INSTALL "Supporting install script" ON)

# global root dir
set(SOLUTION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DOTL_SOLUTION_DIR="${SOLUTION_DIR}")

# dir for common cmake files
list(APPEND CMAKE_MODULE_PATH ${SOLUTION_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${SOLUTION_DIR}/cmake)

# option for platform
set(PLATFORM "auto" CACHE STRING "auto, x86 or x64")
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Debug or Release")
set(CONFIGURATION ${CMAKE_BUILD_TYPE})
option(OTL_WITH_OPENCV "with opencv to compile test files" OFF)

# set common compiler flags
include(LOCAL_FLAGS)
include(LOCAL_ENV)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/build CACHE STRING "set install prefix")
install(CODE "MESSAGE(\"Installing into ${CMAKE_INSTALL_PREFIX}\")")

set(LOCAL_OUTPUT_DIR ${PROJECT_SOURCE_DIR})

if (LOCAL_OUTPUT_DIR)
    set(EXECUTABLE_OUTPUT_PATH ${LOCAL_OUTPUT_DIR}/${ENV_RUNTIME_DIR})
    set(LIBRARY_OUTPUT_PATH ${LOCAL_OUTPUT_DIR}/${ENV_LIBRARY_DIR})
endif ()

add_subdirectory(src)

# project files for clion
#message(STATUS "Project source: ${PROJECT_SOURCE_DIR}")
FILE(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
#message(STATUS "${TEST_FILES}")
FILE(GLOB_RECURSE TOOL_FILES ${PROJECT_SOURCE_DIR}/tools/*.cpp)
#message(STATUS "${TOOL_FILES}")

include_directories(${PROJECT_SOURCE_DIR}/include)

foreach (path ${TEST_FILES})
    string(REGEX MATCH "[^/]*.[(c)|(cc)|(cpp)]$" file_ext ${path})
    string(REGEX MATCH "^[^.]*" file ${file_ext})
    add_executable(test_${file} ${path})
    set_target_properties(test_${file} PROPERTIES OUTPUT_NAME test_${file}${ENV_SUFFIX})
    target_link_libraries(test_${file} ${PROJECT_NAME}_STATIC)
    set_target_properties(test_${file} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LOCAL_OUTPUT_DIR}/lib)

    if(OTL_WITH_OPENCV)
        add_definitions(-DOTL_WITH_OPENCV)
        set(OpenCV_DIR "E:/software_installed/opencv3/opencv3/build")
#        message(STATUS "CMAKE_MODULE_PATH:${CMAKE_MODULE_PATH}")
        find_package(OpenCV REQUIRED)
        include_directories(${OpenCV_INLCUDE_DIRS})
        target_link_libraries(test_${file} ${OpenCV_LIBS})
    endif()

endforeach ()

foreach (path ${TOOL_FILES})
    string(REGEX MATCH "[^/]*.[(c)|(cc)|(cpp)]$" file_ext ${path})
    string(REGEX MATCH "^[^.]*" file ${file_ext})
    add_executable(tool_${file} ${path})
    set_target_properties(tool_${file} PROPERTIES OUTPUT_NAME ${file}${ENV_SUFFIX})
    target_link_libraries(tool_${file} ${PROJECT_NAME}_STATIC)
    install(TARGETS tool_${file}
            RUNTIME DESTINATION ${ENV_RUNTIME_DIR}
            )
endforeach ()