require watchdog/watchdog_advantech.inc

SRC_URI += " \
    file://rtc-support.cfg \
    file://rtl8211f-leds.patch \
    file://rom5722-db2510.dts;subdir=arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
    cp "${UNPACKDIR}/arch/arm64/boot/dts/freescale/rom5722-db2510.dts" "${S}/arch/arm64/boot/dts/freescale/"

    echo 'dtb-$(CONFIG_ARCH_MXC) += rom5722-db2510.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
    watchdog_advantech_patch
}

DELTA_KERNEL_DEFCONFIG += "rtc-support.cfg"
