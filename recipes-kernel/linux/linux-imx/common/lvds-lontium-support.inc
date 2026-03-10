SRC_URI += " \
	file://lvds-lontium-support.cfg \
	file://lt9211-driver-fixup.patch \
"
DELTA_KERNEL_DEFCONFIG += "lvds-lontium-support.cfg"
