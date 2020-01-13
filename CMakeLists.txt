cmake_minimum_required (VERSION 3.5)

set(PROJECT_NAME
  SBRServer)

project(${PROJECT_NAME})

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

find_package(Boost COMPONENTS
        system
        filesystem
        thread
        date_time
        chrono
        regex
        serialization
        program_options
        date_time
        REQUIRED)

include_directories(${Boost_INCLUDE_DIRS}) 
include_directories("ext/crow")
include_directories("ext/abrakm")
include_directories("ext/abrbase")
include_directories("ext/abrstm")
include_directories("ext/sbrcsr")


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")


file (GLOB source_files "${source_dir}/*.cpp")

set(LIBRARIES
        abrakm
        abrbase 
        abrstm
        sbrcsr)

add_executable (${PROJECT_NAME} ${source_files})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
