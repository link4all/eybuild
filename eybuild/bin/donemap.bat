@echo off
rem donemap.bat - script for compile csp files and rom files
rem
rem Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. 
rem
rem modification history
rem --------------------
rem 02a, 2006-11-20 newzy   add support -d option
rem 01d, 2006-5-16  newzy   add support -l option
rem 01c, 2006-03-28 newzy   adjust the location of "END"
rem 01b, 2006-01-22 newzy   separated following and moved to bin/
rem 01a, 2005-12-30 newzy   create 
rem

    set WORKDIR=%2
    set CURRENT_DIR=%1
    set DEST_FILE=%DEST_DIR%/%ROM_MAPLIST%.c
    
    REM clean option if not '-l'
    REM if "%3" neq "-l" set OPTIONS=
    
    REM enter into directory
    cd /d %WORKDIR%
    
    REM COMPILE CSP
    if defined CSP_MAPFILE (
        echo ########## Build csp ########## 
        %EYBUILD_BASE%/bin/csp2bin %CSP_OPTIONS% %CSP_MAPFILE% %CSP_MAPLIST% %DEST_DIR%
    ) 
    
    REM check test result
    if "%errorlevel%" neq "0" (
        goto END;
    )


    if defined ROM_MAPFILE (
        echo.
        echo ########## Build romfile: ########## 
        
        %EYBUILD_BASE%/bin/web2bin %ROM_OPTIONS% %ROM_MAPFILE% %ROM_MAPLIST% %DEST_DIR%
    )

    REM check test result
    if "%errorlevel%" neq "0" (
        goto END;
    )

:END
    REM restore old directory
    cd /d %CURRENT_DIR%

    REM clean all environment
    set DEST_DIR=
    set CSP_MAPFILE=
    set CSP_MAPLIST=
    set ROM_MAPFILE=
    set ROM_MAPLIST=

    echo.
    if "" equ "%3" (
        pause
    )

