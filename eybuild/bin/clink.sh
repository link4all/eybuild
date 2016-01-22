#!/bin/sh
#
# clink.sh - script for compile and link with gcc
#
# Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. 
#
# modification history
# --------------------
# 01a, 2006-7-6  	newzy create
#

echo ==== Enter File: $0 ====

export EYBUILD_BASE=$1; shift
export PATH=$EYBUILD_BASE/bin/:$PATH
export CSP_DEBUG=FALSE

export PROJECT_BASE=

export USR_INC=
export USR_SRCS=
export USR_LIBS=

export CC=gcc

TARGET_PATH=$4
TARGET_NAME=../modules/$5

cd "$TARGET_PATH"
if [ ! -d objs ]; then mkdir -m=rwx objs; fi
if [ ! -d modules ]; then mkdir -m=rwx modules; fi
cd objs

echo "$1 ==> $2"  >cspmap.map
echo "	$3" >>cspmap.map
csp2bin cspmap.map csp_maplist ../cspsrc 

CSP_INCS="../ $EYBUILD_BASE/include"
CSP_LIBS="$EYBUILD_BASE/lib/libeybuild.a"

if [ "/" = "$2" ]; then
	CSP_SRCS="$TARGET_PATH/cgimain.c $TARGET_PATH/cspsrc/csp_maplist.c"
else
	CSP_SRCS="$TARGET_PATH/../cgimain.c $TARGET_PATH/cspsrc/csp_maplist.c"
fi

INCS=
for inc in $CSP_INCS $USR_INC
do 
	INCS="$INCS -I$inc"
done

rm -f $TARGET_NAME
$CC -g -s -shared $CC_OPTS -DHAVE_CSP_ENGINE $INCS \
		-o $TARGET_NAME $CSP_SRCS $USR_SRCS $CSP_LIBS $USR_LIBS 2>&1

echo ==== Exit File : $0 ====
