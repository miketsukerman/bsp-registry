SRC_URI += " \
	file://0001-minimal-differences.patch \
	file://lpddr4_timing_rom5721a1_2G.c;subdir=board/freescale/imx8mm_evk \
"

do_configure:prepend() {
	cp "${UNPACKDIR}/board/freescale/imx8mm_evk/lpddr4_timing_rom5721a1_2G.c" "${S}/board/freescale/imx8mm_evk/"

	sed -i "/^CONFIG_DEFAULT_FDT_FILE=/c\CONFIG_DEFAULT_FDT_FILE=\"rom5721-db5901.dtb\"" ${S}/configs/imx8mm_evk_defconfig
}
