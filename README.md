# petalinux

Zynq SoC构建linux的uboot、kernel、rootfs、driver等相关配置和流程，主要实现axi-adc-dma驱动。

## Notice:
* Vivado 和 Petalinux版本均为2019.1，必须保持一致。
更具体地说，不同Vivado版本生成的hdf文件是不同的，所以不可以混用。另外，不同Petalinux版本对使用的linux内核版本也有要求，尽量用默认配置自动获取。

* 在使用petalinux命令前需要设置环境变量，例如:
```bash
source ~/Software/Xilinx/Petalinux/settings.sh
source ~/Software/Xilinx/Vivado/2019.1/settings64.sh
```
为了方便，可以创建一个文件"petaenv"，就是以上内容。并把所在路径加入到环境变量PATH中。后续就可以直接使"source petaenv"。

* Ubuntu 18.04.2 LTS

## Workflow Example
```bash
source petaenv
petalinux-create --type project --template zynq --name ax_peta

# build kernel and rootfs
cd ax_peta
petalinux-config --get-hw-description ../proj.sdk
petalinux-config -c kernel
petalinux-config -c rootfs

# driver modules. optional!
petalinux-create -t modules -n mymodule --enable
petalinux-build -c mymodule

# compile uboot、kernel、rootfs、device tree...
petalinux-build

# generate boot file
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga --u-boot --force
```
Output files in "images/linux/"


## Develop Kernel Driver

* 为了更好的维护性，驱动模块使用petalinux创建，都在此目录下："project-spec/meta-user/recipes-modules/"。以下操作都在上述目录，首先配置环境：
```bash
cd env
cp cmake.env.example cmake.env
cp make.env.example make.env
```
然后修改里面的源码目录。env主要配置源码位置，最好拷贝出一份工具自动下载的源码("build/tmp/work-shared/plnx-zynq7/kernel-source")，并编译一下。
          
* 驱动程序用petalinux编译特别慢，为了方便开发和调试，可使用build.mk手动编译。
```bash
cd adcmodule/files
make -f build.mk
```

* 为了更好的IDE支持，可直接用CLion等IDE加载CMake工程进行开发。

# Links
* [ug1144-petalinux-tools-reference-guide.pdf](https://www.xilinx.com/support/documentation/sw_manuals/xilinx2019_1/ug1144-petalinux-tools-reference-guide.pdf)
* [ug1157-petalinux-tools-command-line-guide.pdf](https://www.xilinx.com/support/documentation/sw_manuals/xilinx2019_1/ug1157-petalinux-tools-command-line-guide.pdf)
* [xapp1183-zynq-xadc-axi.pdf](https://www.xilinx.com/support/documentation/application_notes/xapp1183-zynq-xadc-axi.pdf)
