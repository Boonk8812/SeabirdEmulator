# Set the minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Seabird VERSION 0.0.1)

# Add the source files to the build
set(SOURCES
  src/
  bin/
  emulator/
)

# Compile the sources into object files
add_library(Seabird OBJECT ${SOURCES})

# Link the object files into an executable
add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:sea_bird_emulator>)

# Set include directories for the project
target_include_directories(Seabird PRIVATE
  src
  # add include directories here as needed
)

# Set link libraries for the project
target_link_libraries(Seabird PRIVATE
  # add link libraries here as needed
)

# Set compiler options for the project
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
