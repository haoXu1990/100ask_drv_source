# 注意配置 KERN_DIR 和 CROSS_COMPILE 环境变量
# export ARCH=arm64
# export CROSS_COMPILE=aarch64-linux-gnu-
# export PATH=$PATH:/home/book/100ask_imax6ull/ToolChain-

KERN_DIR = /home/book/100ask_imax6ull/Linux-4.88

all:
	make -C $(KERN_DIR) M=`pwd` modules
	$(CROSS_COMPILE)gcc - o hello_drv_test hello_drv_test.c

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order
	rm -f hello_drv_test

obj-m += hello_drv.o