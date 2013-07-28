#
#   Repattern Library
#   Copyright (C) 2013 Bindle Binaries <syzdek@bindlebinaries.com>.
#
#   @BINDLE_BINARIES_BSD_LICENSE_START@
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are
#   met:
#
#      * Redistributions of source code must retain the above copyright
#        notice, this list of conditions and the following disclaimer.
#      * Redistributions in binary form must reproduce the above copyright
#        notice, this list of conditions and the following disclaimer in the
#        documentation and/or other materials provided with the distribution.
#      * Neither the name of Bindle Binaries nor the
#        names of its contributors may be used to endorse or promote products
#        derived from this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
#   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#   SUCH DAMAGE.
#
#   @BINDLE_BINARIES_BSD_LICENSE_END@
#
#   @configure_input@
#
#   Makefile.am - automate compiling on a unix platform
#

# Sub directories
SUBDIRS					=
DIST_SUBDIRS				=


# Global flags
AM_LIBS					=
AM_LDFLAGS				= -L$(top_builddir)/lib
AM_CFLAGS				= -O2 $(CFLAGS_WARNINGS)
AM_CXXFLAGS				= -O2 @AM_CXXFLAGS@
AM_OBJCFLAGS				= -O2 @AM_OBJCFLAGS@
AM_CPPFLAGS				= -O2 -UPMARK -DHAVE_CONFIG_H=1 -I$(top_builddir)/include -I$(top_srcdir)/include
ACLOCAL_AMFLAGS				= -I m4 -W all -W error
AM_MAKEINFOFLAGS                        = --no-split
DEFS					=


# automake targets
check_PROGRAMS				=
doc_DATA				=
include_HEADERS				= include/repattern.h \
					  include/repattern-strings.h
lib_LTLIBRARIES				= lib/librepattern.la
man_MANS				=
info_TEXINFOS				=
noinst_DATA				=
noinst_LTLIBRARIES			=
noinst_HEADERS				=
noinst_PROGRAMS				=
noinst_SCRIPTS				=
bin_PROGRAMS				= src/repattern
bin_SCRIPTS				=
sbin_SCRIPTS				=

# lists
SRCHEADERS				= $(srcdir)/include/repattern-strings-header.h \
					  $(srcdir)/include/repattern-strings-internet.h \
					  $(srcdir)/include/repattern-strings-footer.h
BUILT_SOURCES				= include/repattern-strings.h
TESTS					= $(noinst_SCRIPTS)
XFAIL_TESTS				=
EXTRA_MANS				=
EXTRA_DIST				= build-aux/git-tar-name.txt \
					  contrib/bindletools/COPYING \
					  contrib/bindletools/README \
					  contrib/bindletools/build-aux/autogen.sh \
					  contrib/bindletools/build-aux/git-package-version.sh \
					  contrib/bindletools/build-aux/makefile-autotools.am \
					  contrib/bindletools/build-aux/makefile-subst.am \
					  contrib/bindletools/build-aux/makefile-version.am \
					  contrib/bindletools/include/bindle/regex.h \
					  contrib/bindletools/m4/bindle-gcc.m4 \
					  contrib/bindletools/m4/bindle-git.m4 \
					  lib/librepattern.sym \
					  $(SRCHEADERS)
CLEANFILES				= \
					  $(builddir)/a.out   $(srcdir)/a.out \
					  $(builddir)/*/a.out $(srcdir)/*/a.out \
					  config.h.in~ $(srcdir)/config.h.in~ \
					  $(man_MANS) \
					  include/repattern-strings.h \
					  @PACKAGE_TARNAME@-*.tar.* \
					  @PACKAGE_TARNAME@-*.zip
DISTCHECK_CONFIGURE_FLAGS		= --enable-strictwarnings


# macros for lib/libbindle.la
lib_librepattern_la_DEPENDENCIES	= Makefile lib/librepattern.sym $(include_HEADERS)
lib_librepattern_la_LDFLAGS		= -rpath'$(libdir)'\
					  -version-info $(LIB_VERSION_INFO) \
					  $(AM_LDFLAGS) \
					  -export-symbols $(srcdir)/lib/librepattern.sym
lib_librepattern_la_SOURCES		= \
					  lib/librepattern-api.c \
					  lib/librepattern-api.h \
					  lib/librepattern-re.c \
					  lib/librepattern-re.h \
					  lib/librepattern-re-internet.c \
					  lib/librepattern-re-internet.h \
					  lib/librepattern-version.c \
					  lib/librepattern-version.h


# macros for src/aputils-sql
src_repattern_DEPENDENCIES		= lib/librepattern.la
src_repattern_LDADD			= lib/librepattern.la
src_repattern_CPPFLAGS			= $(AM_CPPFLAGS)
src_repattern_SOURCES			= src/repattern.c


# Makefile includes
GIT_PACKAGE_VERSION_DIR=include
include $(srcdir)/contrib/bindletools/build-aux/makefile-autotools.am
include $(srcdir)/contrib/bindletools/build-aux/makefile-subst.am
include $(srcdir)/contrib/bindletools/build-aux/makefile-version.am


# custom targets
.PHONY:

include/repattern-strings.h: Makefile $(SRCHEADERS)
	@mkdir -p `dirname $(@)`
	@rm -f $(@)
	cat $(SRCHEADERS) > $(@) || rm -f $(@)


# local targets
install-exec-local:

install-data-local:

uninstall-local:

clean-local:

distclean-local:
	rm -fR $(srcdir)/autom4te.cache

# end of automake file
