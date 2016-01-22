@echo off
rem project-map.bat - to run domap in IDE environment
rem
rem Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. 
rem
rem modification history
rem --------------------
REM 
rem 02a, 2006-11-24 newzy   add support -cpp and help
rem 02a, 2006-11-20 newzy   add support -d option
rem 01a, 2006-4-11  newzy	create 
rem

rem No parameter specified
if "" equ "%1" (
	echo No parameter specified
	goto help
)

rem Not find map tool
set MAP_TOOL=%1\domap.bat
if not exist %MAP_TOOL% (
	echo *** error ***: 
	echo   Not find map tool: %MAP_TOOL%.
	echo   Please check is this project for eybuild.
	goto END
) 

rem set options
if "%2" equ "-cpp" (
	set CSP_OPTIONS=%2
	shift
)
set CSP_OPTIONS=%CSP_OPTIONS% %2
set ROM_OPTIONS=%3

rem do map
call %MAP_TOOL% /nopause

@echo off
goto END

:help
	echo %~n0 - project map
	echo Usage: %~n0 [base-dir] [-cpp] [-d^|-d0^|-d1] [-d]
	echo   base-dir        - project current directory, example: "$(WkspDir)
	echo   -cpp            - csp2bin compile for C++, see csp2bin
	echo   -d*	            - csp2bin compress or not
	echo   -d              - web2bin compress or not
	
:END
for %%I in (%2 %3 %4 %5 %6) do (
    if "/pause" equ "%%I" (
	    pause
	)
)

