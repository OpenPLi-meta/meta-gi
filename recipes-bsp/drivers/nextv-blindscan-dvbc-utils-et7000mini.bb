DESCRIPTION = "Utils for DVB-C blindscan"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "http://downloads.openpli.org/archive/gi/xpeedc-dvbc-blindscan-${PV}.zip"

PROVIDES += "virtual/blindscan-dvbc"
RPROVIDES_${PN} += "virtual/blindscan-dvbc"

PV = "1.5"
PR = "r3"

S = "${WORKDIR}"

do_compile() {
}

do_install() {
	install -d "${D}/${bindir}"
	install -m 0755 "${S}/tda1002x" "${D}/${bindir}"
}

INHIBIT_PACKAGE_STRIP = "1"

SRC_URI[md5sum] = "28bcf3cd9de63144d7b0bbf9d5040e74"
SRC_URI[sha256sum] = "05c99af948d6fd1e17765698db5e4be46d1deda868ed0b84f5b03f6af8667200"
