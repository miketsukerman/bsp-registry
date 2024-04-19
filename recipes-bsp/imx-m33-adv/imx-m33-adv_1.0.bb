DESCRIPTION = "Advantech M33 demo for iMX8ulp"
LICENSE = "CLOSED"

inherit deploy

SRC_URI = "git://git@ssh.dev.azure.com/v3/AdvEECC/EECC_Internal/sdk_imx8ulp_adv;protocol=ssh;branch=master"
SRCREV = "a2dab8cd091dfb2c564e103aa57fd41b919f641e"

S = "${WORKDIR}/git"

DEPENDS += "cmake-native gcc-arm-none-eabi-native"

do_compile() {
	local td=${S}/application/armgcc
	local tgt=$td/release/adv_imxcm33.bin
	local tcb=$(dirname $(which arm-none-eabi-gcc))
	local tcd=$tcb/..

	export ARMGCC_DIR=$tcd

	cd "$td" && ./build_release.sh && cp "$tgt" "${S}/"
}

do_install() {
	local tr=${S}/application/armgcc/release

	install -d ${D}${base_libdir}/firmware
	install -m 0644 ${tr}/*.elf ${D}${base_libdir}/firmware
}

DEPLOY_FILE_EXT ?= "bin"

do_deploy() {
	install -m 0644 ${S}/*.${DEPLOY_FILE_EXT} ${DEPLOYDIR}/
}

addtask deploy after do_install

PACKAGE_ARCH = "${MACHINE_SOCARCH}"

FILES:${PN} = "${nonarch_base_libdir}/firmware"

INSANE_SKIP:${PN} = "arch"
