cmake_minimum_required(VERSION 3.15)
project(SpaceInvader)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Optionally set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add raylib
# Option 1: Use raylib installed on your system (e.g., via package manager)
find_package(raylib REQUIRED)
# Add your source files
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/spaceship.cpp
    src/game.cpp
    src/bullet.cpp
    src/block.cpp
    src/obstacle.cpp
    src/alien.cpp
    # Add other .cpp files here
)

file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

#Link with include
target_include_directories(${PROJECT_NAME}
PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link with raylib and other required libraries
target_link_libraries(${PROJECT_NAME}
    raylib
)

# Add platform-specific libraries if needed
if(WIN32)
  # Nothing extra typically needed
elseif(APPLE)
  find_library(COCOA_LIBRARY Cocoa REQUIRED)
  find_library(IOKIT_LIBRARY IOKit REQUIRED)
  find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
  target_link_libraries(${PROJECT_NAME} ${COCOA_LIBRARY}
  ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
elseif(UNIX)
  target_link_libraries(${PROJECT_NAME} pthread dl m)
endif()
