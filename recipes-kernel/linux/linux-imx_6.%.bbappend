FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

require recipes-kernel/linux/linux-imx/${MACHINE}.inc

LOCALVERSION = "-adv-modbsp"
