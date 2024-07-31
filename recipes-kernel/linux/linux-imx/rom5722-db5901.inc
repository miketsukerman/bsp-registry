SRC_URI += " \
    file://rom5722-db5901.dts;subdir=git/arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
    echo 'dtb-$(CONFIG_ARCH_MXC) += rom5722-db5901.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
}