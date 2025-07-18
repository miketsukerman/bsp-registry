SRC_URI += " \
	file://0001-minimal-differences.patch \
	file://lpddr4_timing_rom5720a1_2G.c;subdir=board/freescale/imx8mq_evk \
	file://lpddr4_timing_b0.c;subdir=board/freescale/imx8mq_evk \
"

do_configure:prepend() {
	cp "${UNPACKDIR}/board/freescale/imx8mq_evk/lpddr4_timing_rom5720a1_2G.c" "${S}/board/freescale/imx8mq_evk/"

	where=${S}/configs/imx8mq_wevk_defconfig
	tag=CONFIG_IMX8MQ_4GB_DDR_TIMING

	sed -i "/^$tag=/c$tag=n" "$where"

	tag=CONFIG_DEFAULT_FDT_FILE

	if grep -q "$tag" "$where" ; then
		sed -i "/^$tag=/c$tag=\"rom5720-db5901.dtb\"" "$where"
	fi

	replace=fdtfile=rom5720-db5901.dtb
	find=fdtfile=imx8mq-evk.dtb
	where=${S}/include/configs/imx8mq_evk.h

	if grep -q "$find" "$where" ; then
		sed -i "s/$find/$replace/g" "$where"
	fi
}
