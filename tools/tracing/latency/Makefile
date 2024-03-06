# SPDX-License-Identifier: GPL-2.0-only

ifeq ($(srctree),)
  srctree	:= $(patsubst %/,%,$(dir $(CURDIR)))
  srctree	:= $(patsubst %/,%,$(dir $(srctree)))
  srctree	:= $(patsubst %/,%,$(dir $(srctree)))
endif

ifeq ($(OUTPUT),)
  OUTPUT	:= $(CURDIR)/
endif

LATENCY-COLLECTOR	:= $(OUTPUT)latency-collector
LATENCY-COLLECTOR_IN	:= $(LATENCY-COLLECTOR)-in.o

export CC	:= gcc
export LD	:= ld
export AR	:= ar
export PKG_CONFIG := pkg-config

FEATURE_TESTS	:= libtraceevent
FEATURE_TESTS	+= libtracefs
FEATURE_DISPLAY	:= libtraceevent
FEATURE_DISPLAY	+= libtracefs

ifeq ($(V),1)
  Q 		=
else
  Q 		= @
endif

all: $(LATENCY-COLLECTOR)

include $(srctree)/tools/build/Makefile.include
include $(srctree)/tools/build/Makefile.feature
include $(srctree)/tools/scripts/Makefile.include
include Makefile.config

CFLAGS		+= $(INCLUDES) $(LIB_INCLUDES)

export CFLAGS OUTPUT srctree

$(LATENCY-COLLECTOR): $(LATENCY-COLLECTOR_IN)
	$(QUIET_LINK)$(CC) $(LDFLAGS) -o $(LATENCY-COLLECTOR) $(LATENCY-COLLECTOR_IN) $(EXTLIBS)

latency-collector.%: fixdep FORCE
	make -f $(srctree)/tools/build/Makefile.build dir=. $@

$(LATENCY-COLLECTOR_IN): fixdep FORCE
	make $(build)=latency-collector

INSTALL		:= install
MKDIR		:= mkdir
STRIP		:= strip
BINDIR		:= /usr/bin

install:
	@$(MKDIR) -p $(DESTDIR)$(BINDIR)
	$(call QUIET_INSTALL,latency-collector)$(INSTALL) $(LATENCY-COLLECTOR) -m 755 $(DESTDIR)$(BINDIR)
	@$(STRIP) $(DESTDIR)$(BINDIR)/latency-collector

clean:
	$(call QUIET_CLEAN, latency-collector)
	$(Q)find . -name '*.o' -delete -o -name '\.*.cmd' -delete -o -name '\.*.d' -delete
	$(Q)@rm -f latency-collector fixdep FEATURE-DUMP
	$(Q)rm -rf feature

.PHONY: FORCE clean install
