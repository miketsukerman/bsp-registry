require common/lvds-lontium-support.inc

SRC_URI += " \
    file://rom2620-ed91.dts;subdir=arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
    cp "${UNPACKDIR}/arch/arm64/boot/dts/freescale/rom2620-ed91.dts" "${S}/arch/arm64/boot/dts/freescale/"

    echo 'dtb-$(CONFIG_ARCH_MXC) += rom2620-ed91.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
}
