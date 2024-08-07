SRC_URI += " \
    file://rom5722-db2510.dts;subdir=git/arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
    echo 'dtb-$(CONFIG_ARCH_MXC) += rom5722-db2510.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
}