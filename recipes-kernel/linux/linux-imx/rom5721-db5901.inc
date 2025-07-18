SRC_URI += " \
	file://rom5721-db5901.dts;subdir=arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
	cp "${UNPACKDIR}/arch/arm64/boot/dts/freescale/rom5721-db5901.dts" "${S}/arch/arm64/boot/dts/freescale/"

	echo 'dtb-$(CONFIG_ARCH_MXC) += rom5721-db5901.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
}
