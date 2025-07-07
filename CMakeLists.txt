cmake_minimum_required(VERSION 3.10)

set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_OBJCOPY riscv32-unknown-elf-objcopy)
set(CMAKE_C_COMPILER riscv32-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER riscv32-unknown-elf-g++)
set(CMAKE_ASM_COMPILER riscv32-unknown-elf-gcc)
set(_CMAKE_TOOLCHAIN_PREFIX riscv32-unknown-elf-)

set(TARGET_ARCH "rv32imaczicsr_zifencei")

set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/memory.ld")

set(CMAKE_C_FLAGS "-march=${TARGET_ARCH} -mabi=ilp32 -Wall -Wextra -Wno-main -Os -flto -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-march=${TARGET_ARCH} -Wl,--gc-sections -nostartfiles -fno-exceptions --specs=sim.specs -T ${LINKER_SCRIPT}")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

project(embive_c_template C CXX ASM)

set(TARGET app)

add_executable(${TARGET}.elf src/entry.s src/embive.c src/main.c)

set_target_properties(${TARGET}.elf PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}")
target_include_directories(${TARGET}.elf PRIVATE ./include/ )
