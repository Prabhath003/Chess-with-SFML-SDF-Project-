cmake_minimum_required(VERSION 3.0.0)

# set project name
project(main VERSION 1.0)

# set cmake standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(EXEC main)

# Enabling default debug symbols
if(NOT CMAKE_BULD_TYPE)
    set(CMAKE_BUILD_TYPE Debug
      CACHE STRING
        "Choose the type of build (Debug or Release)" FORCE)
endif()

# Find SFML shared libraries
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
include_directories(include)
# Compile 
file(GLOB SOURCES src/*.cpp)
add_executable(${EXEC} ${SOURCES})


# Link executable to required SFML modules
target_link_libraries(main sfml-graphics sfml-audio)

# Set executable install location
install(TARGETS main DESTINATION bin)

# add subdirectory testFiles
add_subdirectory(testFiles)

add_library(${EXEC}_lib STATIC ${SOURCES})

