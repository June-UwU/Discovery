cmake_minimum_required(VERSION 3.15)
project(Discovery C)

# Enforce C11 standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set the C compiler
set(CMAKE_C_COMPILER arm-none-eabi-gcc)

# Set the linker script file
set(LINKER_FILE ${CMAKE_CURRENT_SOURCE_DIR}/startup/linker.ld)

# Add executable target with source files
add_executable(${PROJECT_NAME} main.c ${CMAKE_CURRENT_SOURCE_DIR}/startup/startup.c)

# Add linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_FILE}")

# Specify the target's hardware architecture and CPU
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m4 -mthumb -nostdlib")

# Add definitions
add_definitions(-DSTM32F4xx)