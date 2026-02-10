FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append:aom5521-db2510 = " \
                    file://0001-oei-add-imx95-aom5521a1-16G-lpddr5.patch \
				    file://0002-oei-add-imx95-aom5521a1-8G-lpddr5.patch \
                    "
SRCREV:aom5521-db2510 = "9f2da5cde3c68a3bb20a25770e8f6ed485072c40"
