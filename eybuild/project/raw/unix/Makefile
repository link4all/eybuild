# 
# Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved.
#
# 01d, 2006-4-11  newzy add support FastCGI
# 01c, 2006-3-23  newzy add get current directory
# 01b, 2006-3-22  newzy change directory
# 01a, 2006-2-15  newzy create
#

# FastCGI Support Option
# HAVE_FASTCGI	= TRUE

TARGET_FILE		= raw.cgi 
CGI_TARGET_PATH	= .
FCGI_TARGET_PATH= .

SRCBASE	= ..
SRC 	= $(SRCBASE)/cgimain.c

ifneq (TRUE, $(findstring TRUE, $(HAVE_FASTCGI)))
	TARGET		= $(CGI_TARGET_PATH)/$(TARGET_FILE)
else
	TARGET		= $(FCGI_TARGET_PATH)/$(patsubst %.cgi,%.fcgi, $(TARGET_FILE)) 
	FASTCGI_LIB = /usr/local/lib/libfcgi.a
endif

RM		= rm -r -f
CC		= gcc
CFLAGS	= -O2 -I$(EYBUILD_BASE)/include 
LIBS	= 

# support FastCGI
ifeq (TRUE, $(findstring TRUE, $(HAVE_FASTCGI)))
	CFLAGS	+= -DHAVE_FASTCGI
	LIBS	+= $(EYBUILD_BASE)/lib/fastcgi/libeybuild.a $(FASTCGI_LIB)
else
	LIBEYBUILD	?= $(EYBUILD_BASE)/lib/libeybuild.a 
	LIBS	+= $(LIBEYBUILD)
endif

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(FCGI_FLAG) -o $@ $^ $(LIBS)

all:
	@# @chmod +x domap.unix
	@# @./domap.unix
	@echo "########## Create '$(TARGET)' ##########"
	$(MAKE) $(TARGET)
	@echo Create OK!
	@echo


clean:
	@echo clean target files...
	@if [ -f $(TARGET) ];	then \
		$(RM) $(TARGET); \
	fi
	@if [ -f "../cspsrc/csp_maplist.c" ];   then \
		$(RM) ../cspsrc/csp_maplist.c; \
		$(RM) ../cspsrc/rom_maplist.c; \
		$(RM) ../cspsrc/csp_p; \
	fi



