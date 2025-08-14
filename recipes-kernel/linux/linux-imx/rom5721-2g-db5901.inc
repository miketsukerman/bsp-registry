SRC_URI += " \
	file://rom5721-db5901.dtsi;subdir=arch/arm64/boot/dts/freescale \
	file://${MACHINE}.dts;subdir=arch/arm64/boot/dts/freescale \
"

do_configure:prepend() {
	cp "${UNPACKDIR}/arch/arm64/boot/dts/freescale/rom5721-db5901.dtsi" \
	   "${UNPACKDIR}/arch/arm64/boot/dts/freescale/${MACHINE}.dts" \
	   "${S}/arch/arm64/boot/dts/freescale/"

	echo "dtb-\$(CONFIG_ARCH_MXC) += ${MACHINE}.dtb" \
				>> ${S}/arch/arm64/boot/dts/freescale/Makefile
}
