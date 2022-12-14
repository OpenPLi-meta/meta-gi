IMAGE_FSTYPES ?= "tar.bz2"

TARGET_ARCH = "arm"
DEFAULTTUNE = "armv7ahf-neon"

MACHINE_KERNEL_PR = "r0"

require conf/machine/include/arm/arch-armv7a.inc
require conf/machine/include/nextv-essential.inc

KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

IMAGE_INSTALL_append += "\
    nextv-initrd-${MACHINE} \
    "

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = "\
    nextv-dvb-modules-${MACHINE} \
    "

#Provider
PREFERRED_PROVIDER_virtual/egl ?= "nextv-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "nextv-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "nextv-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgbm ?= "nextv-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"
PREFERRED_PROVIDER_virtual/kernel = "linux-nextv"

MACHINE_FEATURES += "alsa usbhost wlan 3dtv switchoff osdposition hdmicec"

MACHINE_EXTRA_RRECOMMENDS = " \
	gst-plugin-dvbmediasink \
	ntfs-3g \
	"

PACKAGECONFIG_GL_pn-qtbase = " "
PACKAGECONFIG_append_pn-qtbase += " gles2 linuxfb"

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"

IMAGEDIR ?= "${MACHINE}"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_tar_prepend = "\
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    cp ${IMAGE_ROOTFS}/boot/update.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/update.bin; \
    cp ${DEPLOY_DIR_IMAGE}/zImage ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
    echo ${IMAGEVERSION} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
    echo "rename this file to 'force' to force an update without confirmation" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/noforce; \
    cd ${IMAGE_ROOTFS}; \
    rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
    tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
    mv ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
    bzip2 ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.rootfs.tar.bz2; \
    rm -f ${DEPLOY_DIR_IMAGE}/.tar.bz2; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.manifest; \
    rm -f ${DEPLOY_DIR_IMAGE}/.manifest; \
    rm -Rf ${IMAGEDIR}; \
"
