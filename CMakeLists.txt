cmake_minimum_required(VERSION 3.10)

set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER riscv32-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER riscv32-unknown-elf-g++)
set(CMAKE_ASM_COMPILER riscv32-unknown-elf-gcc)
set(_CMAKE_TOOLCHAIN_PREFIX riscv32-esp-elf-)

set(CMAKE_C_FLAGS "-march=rv32im -mabi=ilp32 -Wall -Wextra -Wno-main -Os")
set(CMAKE_CXX_FLAGS "-march=rv32im -mabi=ilp32 -Wall -Wextra -Wno-main -Os")
set(CMAKE_EXE_LINKER_FLAGS "-march=rv32im -nostartfiles -T ${CMAKE_CURRENT_SOURCE_DIR}/memory.ld")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

project(embive_c_template C)

set ( TARGET app )

add_executable(${TARGET}.elf src/main.c src/embive.c)

set_target_properties(${TARGET}.elf PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}")
target_include_directories(${TARGET}.elf PRIVATE ./include/ )

add_custom_command(TARGET ${TARGET}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary  ${TARGET}.elf  ${TARGET}.bin
        COMMENT "Invoking: Objcopy")

