@echo off
rem ebvar.bat - to set basic environment variables
rem
rem Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. 
rem
rem modification history
rem --------------------
rem 
rem 01a, 2006-7-17  newzy	create 
rem

set CSP_CHKDATE=FALSE
set CUR_PATH=%~dp0
set EYBUILD_BASE=%CUR_PATH:\bin\=%

rem add to environ
set PATH=%EYBUILD_BASE%\bin;%PATH%
