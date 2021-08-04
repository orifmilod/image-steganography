cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
project(kodek)

# set sysroot
# SET(CMAKE_SYSROOT /home/sifu/test-yocto/qemuarmdfs)

file(GLOB PROJECT_SRC
  src/Image.h
  src/Image.cpp
  src/Logger.h
  src/main.cpp
  src/Steganography.h
  src/Steganography.cpp
)

add_subdirectory(libs)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

target_include_directories(${PROJECT_NAME} INTERFACE libs)

# install(TARGETS ${PROJECT_SRC} DESTINATION bin)
