################################################################################
#
# libiopccmd_client
#
################################################################################

LIBIOPCCMD_CLIENT_VERSION       = <BUILDROOT_VERSION>
LIBIOPCCMD_CLIENT_VERSION_MAJOR = 1
LIBIOPCCMD_CLIENT_VERSION_MINOR = 0
LIBIOPCCMD_CLIENT_SITE          = $(call github,YuanYuLin,libiopccmd_client,$(LIBIOPCCMD_CLIENT_VERSION))
#LIBIOPCCMD_CLIENT_SITE          = file:///tmp
#LIBIOPCCMD_CLIENT_SOURCE        = libiopccmd_client.tar.bz2
LIBIOPCCMD_CLIENT_LICENSE       = GPLv2+
LIBIOPCCMD_CLIENT_LICENSE_FILES = COPYING
LIBIOPCCMD_CLIENT_INSTALL_STAGING = YES

LIBIOPCCMD_CLIENT_PACKAGE_DIR	= $(BASE_DIR)/packages/libiopccmd_client

LIBIOPCCMD_CLIENT_DEPENDENCIES  = host-pkgconf json-c

LIBIOPCCMD_CLIENT_EXTRA_CFLAGS =                                        \
	-DTARGET_LINUX -DTARGET_POSIX                           \


LIBIOPCCMD_CLIENT_MAKE_ENV =                       \
	CROSS_COMPILE=$(TARGET_CROSS)       \
	BUILDROOT=$(TOP_DIR)                \
	SDKSTAGE=$(STAGING_DIR)             \
	TARGETFS=$(LIBIOPCCMD_CLIENT_PACKAGE_DIR)  \
	TOOLCHAIN=$(HOST_DIR)/usr           \
	HOST=$(GNU_TARGET_NAME)             \
	SYSROOT=$(STAGING_DIR)              \
	JOBS=$(PARALLEL_JOBS)               \
	$(TARGET_CONFIGURE_OPTS)            \
	CFLAGS="$(TARGET_CFLAGS) $(LIBIOPCCMD_CLIENT_EXTRA_CFLAGS)"

define LIBIOPCCMD_CLIENT_BUILD_CMDS
	$(LIBIOPCCMD_CLIENT_MAKE_ENV) $(MAKE) -C $(@D)
endef

define LIBIOPCCMD_CLIENT_INSTALL_STAGING_CMDS
	$(INSTALL) -m 0755 -D $(@D)/libiopccmd_client.so* $(STAGING_DIR)/usr/lib/
	@mkdir -p $(STAGING_DIR)/usr/include/iopccommon
	$(INSTALL) -m 0644 -D $(@D)/*.h $(STAGING_DIR)/usr/include/iopccommon
endef

define LIBIOPCCMD_CLIENT_INSTALL_TARGET_DIR
	mkdir -p $(TARGET_DIR)/usr/lib/
	cp -avr $(LIBIOPCCMD_CLIENT_PACKAGE_DIR)/usr/lib/* $(TARGET_DIR)/usr/lib/
endef

define LIBIOPCCMD_CLIENT_INSTALL_TARGET_CMDS
	rm -rf $(LIBIOPCCMD_CLIENT_PACKAGE_DIR)
	mkdir -p $(LIBIOPCCMD_CLIENT_PACKAGE_DIR)/usr/lib/
	$(INSTALL) -m 0755 -D $(@D)/libiopccmd_client.so $(LIBIOPCCMD_CLIENT_PACKAGE_DIR)/usr/lib/libiopccmd_client.so.$(LIBIOPCCMD_CLIENT_VERSION_MAJOR).$(LIBIOPCCMD_CLIENT_VERSION_MINOR)
	ln -s libiopccmd_client.so.$(LIBIOPCCMD_CLIENT_VERSION_MAJOR).$(LIBIOPCCMD_CLIENT_VERSION_MINOR) $(LIBIOPCCMD_CLIENT_PACKAGE_DIR)/usr/lib/libiopccmd_client.so.$(LIBIOPCCMD_CLIENT_VERSION_MAJOR)
	ln -s libiopccmd_client.so.$(LIBIOPCCMD_CLIENT_VERSION_MAJOR) $(LIBIOPCCMD_CLIENT_PACKAGE_DIR)/usr/lib/libiopccmd_client.so
	$(LIBIOPCCMD_CLIENT_INSTALL_TARGET_DIR)
endef

$(eval $(generic-package))
