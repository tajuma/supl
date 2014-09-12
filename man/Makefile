TOP = ..
SUBDIRS = 

include $(TOP)/config.mk

DIST = 	Makefile supl-client.1 supl-proxy.1 supl-cert.1

all: 

install: all
	mkdir -p $(DEB_PREFIX)$(CONF_PREFIX)/share/man/man1
	cp -a supl-client.1 supl-proxy.1 supl-cert.1 $(DEB_PREFIX)$(CONF_PREFIX)/share/man/man1

clean:
	/bin/rm -f distfiles *~

distfiles:
	echo $(addprefix man/,$(DIST)) >> $(TOP)/distfiles
	@for subdir in $(SUBDIRS) ; do \
	    $(MAKE) -C $$subdir distfiles ; \
	done

.PHONY: clean dist distfiles debian install
