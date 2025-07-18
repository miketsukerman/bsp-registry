SRC_URI += " \
    file://watchdog/watchdog_advantech.c;subdir=drivers \
"

watchdog_advantech_patch() {
    grep -q watchdog_advantech.o "${S}/drivers/watchdog/Makefile" ||
    echo 'obj-m += watchdog_advantech.o' >>"${S}/drivers/watchdog/Makefile"

    cp "${UNPACKDIR}/drivers/watchdog/watchdog_advantech.c" "${S}/drivers/watchdog/"
}
