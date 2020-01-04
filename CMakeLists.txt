cmake_minimum_required(VERSION 3.15)
project(chip8)

find_package(Boost 1.68.0 COMPONENTS program_options system)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMMON_SOURCE_FILES
    src/Opcode00E0.cpp
    src/Opcode00EE.cpp
    src/Opcode1nnn.cpp
    src/Opcode2nnn.cpp
    src/Opcode3xkk.cpp
    src/Opcode4xkk.cpp
    src/Opcode5xy0.cpp
    src/Opcode6xkk.cpp
    src/Opcode7xkk.cpp
    src/Opcode8xy0.cpp
    src/Opcode8xy1.cpp
    src/Opcode8xy2.cpp
    src/Opcode8xy3.cpp
    src/Opcode8xy4.cpp
    src/Opcode8xy5.cpp
    src/Opcode8xy6.cpp
    src/Opcode8xy7.cpp
    src/Opcode8xyE.cpp
    src/Opcode9xy0.cpp
    src/OpcodeAnnn.cpp
    src/OpcodeBnnn.cpp
    src/OpcodeCxkk.cpp
    src/OpcodeDxyn.cpp
    src/OpcodeEx9E.cpp
    src/OpcodeExA1.cpp
    src/OpcodeFx07.cpp
    src/OpcodeFx0A.cpp
    src/OpcodeFx15.cpp
    src/OpcodeFx18.cpp
    src/OpcodeFx1E.cpp
    src/OpcodeFx29.cpp
    src/OpcodeFx33.cpp
    src/OpcodeFx55.cpp
    src/OpcodeFx65.cpp
    src/Cpu.cpp
    src/utilities.cpp)

add_library(${CMAKE_PROJECT_NAME} STATIC
    ${COMMON_SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
    stdc++fs)

set(EMULATOR_SOURCE_FILES
    src/${CMAKE_PROJECT_NAME}_emulator.cpp
    src/Emulator.cpp)
add_executable(${CMAKE_PROJECT_NAME}_emulator
    ${EMULATOR_SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME}_emulator
    PRIVATE
    stdc++fs
    pthread
    ${SDL2_LIBRARIES}
    Boost::program_options
    Boost::system
    ${CMAKE_PROJECT_NAME})

set(DISASSEMBLER_SOURCE_FILES
    src/${CMAKE_PROJECT_NAME}_disassembler.cpp
    src/Disassembler.cpp)
add_executable(${CMAKE_PROJECT_NAME}_disassembler
    ${DISASSEMBLER_SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME}_disassembler
    PRIVATE
    stdc++fs
    Boost::program_options
    ${CMAKE_PROJECT_NAME})
