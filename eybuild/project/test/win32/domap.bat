@echo off

REM ########################################################
set DEST_DIR=../cspsrc

set CSP_MAPFILE=../cspmap.map
set CSP_MAPLIST=csp_maplist
set ROM_MAPFILE=../rommap.map
set ROM_MAPLIST=rom_maplist
REM ########################################################

if not defined EYBUILD_BASE (
    echo Not defined "EYBUILD_BASE".
    pause & goto :EOF
)

REM convert file
call %EYBUILD_BASE%/BIN/DONEMAP.BAT %CD% %~dp0 %1
echo on	
