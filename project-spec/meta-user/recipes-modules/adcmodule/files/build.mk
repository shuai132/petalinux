obj-m += axi_adc_dma.o

PWD ?= $(shell pwd)

include ../../env/make.env

all:
	make -C $(KERNEL_SRC) M=$(PWD)