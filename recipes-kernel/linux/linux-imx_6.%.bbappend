FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

require recipes-kernel/linux/linux-imx/${MACHINE}.inc

SRC_URI += " \
    file://common/0001-Revert-serial-imx-Restore-original-RXTL-for-console.patch \
"

LOCALVERSION = "-adv-modbsp"
