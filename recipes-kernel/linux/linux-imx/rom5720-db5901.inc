require common/watchdog_advantech.inc
require common/r8169.inc

SRC_URI += " \
	file://rom5720-db5901.dts;subdir=arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
    cp "${UNPACKDIR}/arch/arm64/boot/dts/freescale/rom5720-db5901.dts" "${S}/arch/arm64/boot/dts/freescale/"

    echo 'override dtb-$(CONFIG_ARCH_MXC) := rom5720-db5901.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
    watchdog_advantech_patch
}
