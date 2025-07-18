SRC_URI += " \
    file://rom2820-ed93.dts;subdir=arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
    cp "${UNPACKDIR}/arch/arm64/boot/dts/freescale/rom2820-ed93.dts" "${S}/arch/arm64/boot/dts/freescale/"

    echo 'dtb-$(CONFIG_ARCH_MXC) += rom2820-ed93.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
}
