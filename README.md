# C/C++ Template for Embive
A simple program that runs inside the Embive interpreter.

## Requirements (to build)
- GCC (riscv32-unknown-elf)
    - Download the [RISC-V toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)
    - Install the dependencies from the README
    - Compile and install it:
        - `$ ./configure --prefix=/opt/riscv --with-arch=rv32gc --with-abi=ilp32`
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
    - `$ cargo add embive --features m_extension`
- Copy the example from Embive's docs/readme.
- Swap the line `let code = ...` to `let code = include_bytes!("../app.bin");`
- Copy the generated `app.bin` to your project
- Run it:  
    - `$ cargo run --release`

## Stack Size
By default, the stack size is set to 512 bytes (0x200).  
You can change this by modifying the `STACK_SIZE` variable in the [linker script](memory.ld).  
The stack size should always be a multiple of 16 bytes.

## RAM calculation
You can calculate the minimum amount of RAM needed by you application with the following equation:  
- `total_ram = data + bss`

To get the `data` and `bss` sizes, you can run:  
- `$ riscv32-unknown-elf-size app.elf`
    - The stack size will be reported as part of the bss

The result should be something like this:
```
   text    data     bss     dec     hex filename
    348       4     512     864     360 app.elf
```

For this result, our minimum RAM size then would be:  
- `total_ram = 4 + 512 = 516 bytes`
