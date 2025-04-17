require drivers/watchdog_advantech.inc

SRC_URI += " \
	file://r8169.cfg \
	file://rom5720-db5901.dts;subdir=git/arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
    echo 'override dtb-$(CONFIG_ARCH_MXC) := rom5720-db5901.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
    watchdog_advantech_patch
}

DELTA_KERNEL_DEFCONFIG += "r8169.cfg"
