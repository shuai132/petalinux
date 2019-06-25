cmake_minimum_required(VERSION 2.8)

include(env/cmake.env)

add_custom_target(adcmodule
        COMMAND cd ${CMAKE_CURRENT_LIST_DIR}/adcmodule/files && make -f build.mk && file *.ko
        )

add_library(ignore
        adcmodule/files/axi_adc_dma.c
        )
