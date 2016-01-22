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

# HAVE_CPLUSPLUS = TRUE
# HAVE_CSP_COMPR = TRUE
# HAVE_ROM_COMPR = TRUE

#
# FCGI_SPEC		where FastCGI target store to
# ARCHIVE_SPEC  where archive target store to
# FILTER_LIST	create archive, filter out following objs
#
TARGET_FILE	= review.cgi 
FCGI_SPEC	= .
ARCHIVE_SPEC= .
FILTER_LIST = 
FASTCGI_LIB	= /usr/local/lib/libfcgi.a


# source list
SRCBASE	= ..
SRCS	= $(SRCBASE)/cgimain.c \
		  $(SRCBASE)/usr/db.c \
		  $(SRCBASE)/usr/login.c


# insert compile tools here
# REDEF_TOOLS = TRUE


# insert more compile options here
CFLAGS = -O2 -Wall -DREMOVE_NOUSED_WARNING -I.. -I../usr


# make rules
-include ../cspsrc/.csp_maplist
-include ../cspsrc/.rom_maplist
include  $(EYBUILD_BASE)/bin/make.rule


#insert more target dependence here



