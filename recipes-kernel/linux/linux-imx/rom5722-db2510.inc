require drivers/watchdog_advantech.inc

SRC_URI += " \
    file://rtc-support.cfg \
    file://rom5722-db2510.dts;subdir=git/arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
    echo 'dtb-$(CONFIG_ARCH_MXC) += rom5722-db2510.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
    watchdog_advantech_patch
}

DELTA_KERNEL_DEFCONFIG += "rtc-support.cfg"
