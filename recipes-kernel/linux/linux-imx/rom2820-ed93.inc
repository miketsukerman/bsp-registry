SRC_URI += " \
    file://rom2820-ed93.dts;subdir=git/arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
    echo 'dtb-$(CONFIG_ARCH_MXC) += rom2820-ed93.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
}