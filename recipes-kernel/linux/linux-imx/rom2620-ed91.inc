SRC_URI += " \
    file://lvds-support.cfg \
    file://lt9211-driver-fixup.patch \
    file://rom2620-ed91.dts;subdir=arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
    cp "${UNPACKDIR}/arch/arm64/boot/dts/freescale/rom2620-ed91.dts" "${S}/arch/arm64/boot/dts/freescale/"

    echo 'dtb-$(CONFIG_ARCH_MXC) += rom2620-ed91.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
}

DELTA_KERNEL_DEFCONFIG += "lvds-support.cfg"
