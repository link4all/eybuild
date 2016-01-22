@echo off
rem clink_vc++.bat - script for compile and link with vc++
rem
rem Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. 
rem
rem modification history
rem --------------------
rem 01a, 2006-7-6  	newzy create
rem

echo ==== Enter File: %0 ====
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: BASIC SETTING
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::
:: spath, vname, tpath, dllname

set PATH=%EYBUILD_BASE%/bin;%PATH%

shift
set TARGET_PATH=%4
set TARGET_NAME=..\modules\%5

if /I "true" equ "false" (
	echo argv[0] = %0
	echo argv[1] = %1
	echo argv[2] = %2
	echo argv[3] = %3
	echo argv[4] = %4
	echo argv[5] = %5
)

::
:: CHANGE CURRENT DIRECTORY
::
cd /d %TARGET_PATH%

if not exist objs mkdir objs
if not exist modules mkdir modules
cd objs
::
:: MAKE CSPMAP.MAP AND DO MAP
::
echo %1 ==^> %2  >cspmap.map
	echo %3 >>cspmap.map
csp2bin cspmap.map csp_maplist ../cspsrc 

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: COMPILE SETTING
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::
:: SET COMPILTER & LINKER OPTIONS
::
set LD_PDB=/pdb:"%TARGET_NAME%" /DEBUG
if "%CSP_DEBUG%" == "TRUE" (
	set CC_OPTS=/Od /W3 /Gm /ZI /GX /FR"./" /Fd"./" /Fo"./"
	set LD_OPTS=%LD_PDB:.so=.pdb%
)

set INC_LIST=%EYBUILD_BASE%/include ../ %USR_INC%
set CSP_SRCS=../cspsrc/csp_maplist.c %USR_SRCS%
set CSP_LIBS=%EYBUILD_BASE%/lib/eybuild.lib  %USR_LIBS%


:: check "cgimain.c" exist or not
echo %CSP_SRCS% | find "cgimain.c"
if /I "0" neq "%ERRORLEVEL%" (
	if "\" equ "%2" (
    	set CSP_SRCS=%TARGET_PATH%/cgimain.c %CSP_SRCS%
	)else (
		if exist "%TARGET_PATH%/../cgimain.c" (
    		set CSP_SRCS=%TARGET_PATH%/../cgimain.c %CSP_SRCS%
    	) else (
    		echo *** error: not find file "%TARGET_PATH%/../cgimain.c"
    		goto :EOF
    	)
    )
)

set CSP_OBJS=
for %%I in (%CSP_SRCS%) do (set CSP_OBJS=!CSP_OBJS! %%~nI.obj)

set CSP_INCS=
for %%I in (%INC_LIST%) do (set CSP_INCS=!CSP_INCS! /I%%I)


::
:: REMOVE DLL
::
if exist "%TARGET_NAME%" (
	del /f /q "%TARGET_NAME%"
)

::
:: COMPILE SOUCE CODE
:: LINK LIBS
::
"%CC%" /nologo /D"WIN32" /c /DHAVE_CSP_ENGINE %CC_OPTS% %CSP_INCS% %CSP_SRCS% 2>&1
if "0" neq "%ERRORLEVEL%" goto :EOF

"%LD%" /dll %LD_OPTS% /out:"%TARGET_NAME%" %CSP_OBJS% %CSP_LIBS% 2>&1
if "0" neq "%ERRORLEVEL%" goto :EOF

::
:: CLEAN NOUSED FILES
::
cd ..
del /f /q modules\*.lib 
del /f /q modules\*.exp 
if "%CSP_DEBUG%" neq "TRUE" (
	del /f /q /s objs
	rmdir /q /s objs
	del /f /q /s cspsrc
	rmdir /q /s cspsrc
)
echo ==== Exit File : %0 ====
