# C/C++ Template for Embive
A simple program that runs inside the Embive interpreter.

## Requirements (to build)
- GCC (riscv32-unknown-elf)
    - Download the [RISC-V toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)
    - Install the dependencies from the README
    - Compile and install it:
        - `$ ./configure --prefix=/opt/riscv --with-arch=rv32imaczicsr_zifencei --with-abi=ilp32`
        - `$ make -j8`
    - Add `/opt/riscv/bin` to your PATH
- CMake
    - `$ apt install cmake`

## How to build
- Create a folder for the build
    - `$ mkdir build && cd build`
- Create Makefile
    - `$ cmake ..`
- Compile the project
    - `$ make`

## How to run
- Create a new project
    - `$ cargo new embive-project && cd embive-project`
- Add Embive as a dependency
    - `$ cargo add embive`
- Copy the example from Embive's docs/readme.
- Swap the line `const ELF_FILE: &[u8] ...` to `const ELF_FILE: &[u8] = include_bytes!("../app.elf");`
- Copy the generated `app.elf` (inside `build` folder) to your project
- Run it:  
    - `$ cargo run --release`

## Stack Size
By default, the stack size is set to 1024 bytes (0x400).  
You can change this by modifying the `STACK_SIZE` variable in the [linker script](memory.ld).  
The stack size should always be a multiple of 16 bytes.

## Heap Size
By default, the heap size is set to 1024 bytes (0x400).  
You can change this by modifying the `HEAP_SIZE` variable in the [linker script](memory.ld).  
The heap end address will always be aligned to 16 bytes.

## RAM calculation
You can calculate the minimum amount of RAM needed by you application with the following equation:  
- `total_ram = data + bss`

To get the `data` and `bss` sizes, you can run:  
- `$ riscv32-unknown-elf-size build/app.elf`
    - The stack and heap will be reported as part of the bss

The result should be something like this:
```
   text    data     bss     dec     hex filename
    308       4    2060    2372     944 app.elf
```

For this result, our minimum RAM size would be:  
- `total_ram = 4 + 2060 = 2064 bytes`
