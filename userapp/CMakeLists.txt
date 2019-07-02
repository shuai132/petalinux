cmake_minimum_required(VERSION 2.8)

project(test)

set(CMAKE_SYSTEM_NAME   Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(TOOLCHAIN_DIR       /home/parallels/Software/Xilinx/SDK/2019.1/gnu/aarch32/lin/gcc-arm-linux-gnueabi/)

set(CMAKE_C_COMPILER    ${TOOLCHAIN_DIR}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER  ${TOOLCHAIN_DIR}/bin/arm-linux-gnueabihf-g++)

set(ELF_FILE ${PROJECT_NAME}.elf)

add_executable(${ELF_FILE}
        src/main.c
        src/adc_capture.c
        )

add_subdirectory(../project-spec/meta-user/recipes-modules/ modules)
