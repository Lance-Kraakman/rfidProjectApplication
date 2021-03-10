# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

#If IOT_SOLUTION_PATH is not defined, use relative path as default value
if(NOT DEFINED ENV{IOT_SOLUTION_PATH})
    get_filename_component(IOT_SOLUTION_PATH "${CMAKE_SOURCE_DIR}/../../.." ABSOLUTE)
    set(ENV{IOT_SOLUTION_PATH} ${IOT_SOLUTION_PATH})
    message(WARNING "Can't detect IOT_SOLUTION_PATH in your environment, we infer it is $ENV{IOT_SOLUTION_PATH}")
endif()


set(EXTRA_COMPONENT_DIRS "./components/Processing/inputProcessing" "./components/Processing/displayProcessing")
set(EXTRA_INCLUDE "./components/Processing/inputProcessing" "./components/Processing/displayProcessing")


include($ENV{IOT_SOLUTION_PATH}/component.cmake)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(main)
