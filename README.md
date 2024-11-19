# C Template for Embive
A simple program that runs inside the Embive interpreter.

## Requirements (to build)
- GCC (riscv32-unknown-elf)
- CMake

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
- Swap the line `let code = ...` to `let code = include_bytes!("../app.bin");`
    - You can also remove the line `ram[..4].copy_from_slice...` (not needed / unused).
- Copy the generated `app.bin` to your project
- Run it:  
    - `$ cargo run --release`

## RAM calculation
You can calculate the minimum amount of RAM needed by you application with the following equation:  
`total_ram = data + bss + stack`

To get the `data` and `bss` sizes, you can run:  
`$ riscv32-unknown-elf-size app.elf`

The result should be something like this:
```
   text    data     bss     dec     hex filename
    144       4       0     148      94 app.elf
```

For this result, if we chose a stack size of 512 bytes, our minimum RAM size then would be:  
`total_ram = 4 + 0 + 512 = 516 bytes`