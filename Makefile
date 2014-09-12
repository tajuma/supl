TOP = .
SUBDIRS = src man

include $(TOP)/config.mk

DEBIAN_DIST = \
  changelog compat control copyright libsupl-dev \
  libsupl.files rules supl.files source/format

DIST = configure Makefile README AUTHORS COPYING INSTALL \
       $(prefix debian/,$(DEBIAN_DIST))

all: 
	$(MAKE) -C src

debian: 
	dpkg-buildpackage -rfakeroot -us -uc -tc

install: all
	$(MAKE) -C src install
	$(MAKE) -C man install

clean:
	$(MAKE) -C src clean
	/bin/rm -f distfiles *~
	/bin/rm -fr debian/supl debian/*~ configure-stamp build-stamp

dist:
	/bin/rm -f distfiles
	$(MAKE) distfiles
	tar zcf supl-$(CONF_VERSION).tar.gz $(cat distfiles)

distfiles:
	echo $(DIST) >> distfiles
	@for subdir in $(SUBDIRS) ; do \
	    $(MAKE) -C $$subdir distfiles ; \
	done

.PHONY: clean dist distfiles debian install
