SRC_URI += " \
    file://lpddr4_timing_rsb3720a2_6G.c;subdir=board/freescale/imx8mp_evk \
    file://rsb3720-u-boot.dtsi;subdir=arch/arm/dts \
    file://rsb3720.dts;subdir=arch/arm/dts \
    file://001-change-uart-mapping.patch \
"

do_configure:prepend() {
    cp "${UNPACKDIR}/board/freescale/imx8mp_evk/lpddr4_timing_rsb3720a2_6G.c" "${S}/board/freescale/imx8mp_evk/lpddr4_timing_rsb3720a2_6G.c"
    cp "${UNPACKDIR}/arch/arm/dts/rsb3720-u-boot.dtsi" "${S}/arch/arm/dts/"
    cp "${UNPACKDIR}/arch/arm/dts/rsb3720.dts" "${S}/arch/arm/dts/"

    sed -i "/^CONFIG_DEFAULT_DEVICE_TREE=/c\CONFIG_DEFAULT_DEVICE_TREE=\"rsb3720\"" ${S}/configs/imx8mp_evk_defconfig
    sed -i "/^CONFIG_DEFAULT_FDT_FILE=/c\CONFIG_DEFAULT_FDT_FILE=\"rsb3720.dtb\"" ${S}/configs/imx8mp_evk_defconfig
    sed -i 's/lpddr4_timing.o/lpddr4_timing_rsb3720a2_6G.o/g' ${S}/board/freescale/imx8mp_evk/Makefile
    sed -i 's/console=ttymxc1,115200/console=ttymxc2,115200/g' ${S}/include/configs/imx8mp_evk.h
    sed -i '/imx8mp-evk.dtb/a\\trsb3720.dtb \\' ${S}/arch/arm/dts/Makefile
}
