cmake_minimum_required(VERSION 3.0.0)

message("***Irrigation application CMakeLists***")

project(irrigation VERSION 0.1.0)

# Global variables
file(GLOB_RECURSE  HEADERS
    include/*.h

)

file(GLOB_RECURSE  SOURCES
    src/*.cpp
)

message("headers: ${HEADERS}")
message("sources: ${SOURCES}")

# Add compile options and definitions
add_compile_options(
    -pthread
    -Wall
    -Werror
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
