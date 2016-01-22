# 
# Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved.
#
# 01e, 2006-5-12  newzy add depend
# 01d, 2006-4-11  newzy add support FastCGI
# 01c, 2006-3-23  newzy add get current directory
# 01b, 2006-3-22  newzy change directory
# 01a, 2006-2-15  newzy create
#

# FastCGI Support Option
# HAVE_FASTCGI	= TRUE

HAVE_CPLUSPLUS = TRUE
# HAVE_CSP_COMPR = TRUE
# HAVE_ROM_COMPR = TRUE

#
# FCGI_SPEC     where FastCGI target store to
# ARCHIVE_SPEC  where archive target store to
# FILTER_LIST   create archive, filter out following objs
#
TARGET_FILE	= cplus.cgi 
FCGI_SPEC	= .
ARCHIVE_SPEC= .
FILTER_LIST = 
FASTCGI_LIB	= /usr/local/lib/libfcgi.a


# source list
SRCBASE	= ..
SRCS	= $(SRCBASE)/cgimain.c


# insert compile tools here
#REDEF_TOOLS = TRUE
PREFIX	= xscale_be-
#PREFIX	= arm-linux-
CC      = $(PREFIX)gcc
CXX     = $(PREFIX)g++
AR      = $(PREFIX)ar
LD      = $(PREFIX)ld
STRIP   = $(PREFIX)strip

ifeq (TRUE, $(REDEF_TOOLS))
ifeq (xscale_be-, $(PREFIX))
	LIBEYBUILD	= $(EYBUILD_BASE)/lib/libeybuild_xscale.a 
else 
ifeq (arm-linux-, $(PREFIX))
	LIBEYBUILD	= $(EYBUILD_BASE)/lib/libeybuild_arm.a 
endif
endif
endif


# insert more compile options here
CFLAGS = -Wall -O2 -DREMOVE_NOUSED_WARNING -DEB_LANG_NUM=3	\
		 -I../lang -I../cspsrc/usr


# make rules
-include ../cspsrc/.csp_maplist
-include ../cspsrc/.rom_maplist
include  $(EYBUILD_BASE)/bin/make.rule


#insert more target dependence here



