SRC_URI += " \
    file://drivers/watchdog_advantech.c \
"

watchdog_advantech_patch() {
    grep -q watchdog_advantech.o "${S}/drivers/watchdog/Makefile" ||
    echo 'obj-m += watchdog_advantech.o' >>"${S}/drivers/watchdog/Makefile"

    cp ${WORKDIR}/drivers/watchdog_advantech.c ${S}/drivers/watchdog/
}
