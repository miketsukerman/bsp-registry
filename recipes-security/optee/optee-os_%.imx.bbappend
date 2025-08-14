DESCRIPTION = "OPTEE OS"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append:rom5721-1g-db5901 = " file://0001-optee-rom5721-1g.patch "
