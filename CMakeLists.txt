# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project Name
project(Robotics_Project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set paths to dependencies
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/third/glfw")
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/third/glad")
set(SDL_DIR "${CMAKE_SOURCE_DIR}/third/vendored")
set(Bullet_DIR "${CMAKE_SOURCE_DIR}/third/bullet3/build_cmake")
set(BULLET_LIBRARY_DIRS "${Bullet_DIR}/lib")

# Include and source directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# Find Bullet Physics
find_package(Bullet REQUIRED CONFIG)

if (Bullet_FOUND)
    message(STATUS "Bullet found: ${Bullet_DIR}")
else()
    message(FATAL_ERROR "Bullet Physics SDK not found!")
endif()

set(BULLET_INCLUDE_DIR ${Bullet_DIR}/${BULLET_ROOT_DIR}/${BULLET_INCLUDE_DIR})
set(BULLET_LIBRARY_DIRS ${Bullet_DIR}/${BULLET_ROOT_DIR}/${BULLET_LIBRARY_DIRS})

# Include directories
include_directories(
    ${GLFW_DIR}/include
    ${GLAD_DIR}/include
    ${INCLUDE_DIR}
    ${SDL_DIR}/include
    ${BULLET_INCLUDE_DIRS}
)

# Add GLFW and SDL
add_subdirectory(${GLFW_DIR})
add_subdirectory(${SDL_DIR}/SDL EXCLUDE_FROM_ALL)

# Add Glad source file
set(GLAD_SOURCES ${GLAD_DIR}/src/glad.c)

# Collect all .cpp files in src/ automatically
file(GLOB SOURCE_FILES "${SRC_DIR}/*.cpp")

# Define executable
set(EXECUTABLE_NAME main)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES} ${GLAD_SOURCES})

# Link libraries
find_package(OpenGL REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC OpenGL::GL)
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC glfw)
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC SDL3::SDL3)
    target_include_directories(${EXECUTABLE_NAME}  PUBLIC ${BULLET_INCLUDE_DIR})
    target_compile_definitions(${EXECUTABLE_NAME}  PUBLIC ${BULLET_DEFINITIONS})
    target_link_directories(${EXECUTABLE_NAME}  PUBLIC ${Bullet_DIR}/${BULLET_ROOT_DIR}/${BULLET_LIBRARY_DIRS})
    target_link_libraries(${EXECUTABLE_NAME}  PUBLIC BulletDynamics BulletCollision LinearMath)
    target_link_directories(${EXECUTABLE_NAME} PUBLIC ${BULLET_LIBRARY_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC 
    ${BULLET_LIBRARY_DIRS}/libBulletDynamics.a
    ${BULLET_LIBRARY_DIRS}/libBulletCollision.a
    ${BULLET_LIBRARY_DIRS}/libLinearMath.a)

# Ensure correct include and link paths for Bullet
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${BULLET_INCLUDE_DIRS})
target_link_directories(${EXECUTABLE_NAME} PUBLIC ${BULLET_LIBRARY_DIRS})

# Set platform-specific OpenGL linking
if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC opengl32)
elseif(APPLE)
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC OpenGL)
else()
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC GL)
endif()

# Specify the CMake binary directory for build output
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
