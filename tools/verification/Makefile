# SPDX-License-Identifier: GPL-2.0-only

include ../scripts/Makefile.include

all: rv

clean: rv_clean

install: rv_install

rv:
	$(call descend,rv)

rv_install:
	$(call descend,rv,install)

rv_clean:
	$(call descend,rv,clean)

.PHONY: all install clean rv rv_install rv_clean
