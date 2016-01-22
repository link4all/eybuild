@echo off
@echo off
rem clink_vc++.bat - user script for compile and link with vc++
rem
rem Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. 
rem
rem modification history
rem --------------------
rem 01a, 2006-7-6  	newzy create
rem

echo ==== Enter File: %0 ====
::####################################################################
:: BASIC SETTING
::####################################################################
::
set OS=Windows_NT
call "C:\Program Files\Microsoft Visual Studio\VC98\bin\VCVARS32.BAT"
call "D:\Program Files\Microsoft Visual Studio\VC98\bin\VCVARS32.BAT"
rem call "D:\Program Files\Microsoft Visual Studio 8\Common7\Tools\vsvars32.bat"
set EYBUILD_BASE=%1
shift
rem VC2005 must set to FALSE
set CSP_DEBUG=TRUE

set PROJECT_BASE=

set USR_INC=
set USR_SRCS=
set USR_LIBS=

rem for VC2005
rem set USR_LIBS=%USR_LIBS% /NODEFAULTLIB:"libc" 

set CC=cl.exe
set LD=link.exe

::####################################################################
:: BASIC SETTING
::####################################################################
::
call "C:\Program Files\Microsoft Visual Studio\VC98\bin\VCVARS32.BAT"
call %EYBUILD_BASE%/BIN/CLINK_VC++.BAT %0 %1 %2 %3 %4 %5 %6 %7 %8
echo ==== Exit File : %0 ====

