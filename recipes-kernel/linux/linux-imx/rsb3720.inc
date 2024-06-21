SRC_URI += " \
    file://rsb3720.dts;subdir=git/arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
    echo 'dtb-$(CONFIG_ARCH_MXC) += rsb3720.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
}