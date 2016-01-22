@echo off
rem denf.bat - to set DelayedExpansion option on or off
rem
rem Copyright(C) eyBuild Group, 2005, 2006. All Rights Reserved. 
rem
rem modification history
rem --------------------
rem 01b, 2003-7-17          Ljy mod /np & usage
rem 01a, 2003-7-16 20:50,   Ljy written
rem
rem DESCRIPTION
rem about DelayedExpansion see "CMD.exe /?", "set /?"
rem
rem when exist %WINDIR%\system\dea.log, option on else off
rem you may open or close it with paramter on/off
rem
rem Usage denf.bat [[on]/[off]] [/np]
rem on  - switch DelayedExpansion to on
rem off - switch DelayedExpansion to off
rem /np - do not pause when finished.
rem if no paramters, switch between on/off
rem

setlocal
    rem check whether fit this system
    if not defined WINDIR (
        echo System error, exit...
        pause &exit
    )

    set REG_FILE=%WINDIR%\system\dea.reg
    set REG_LOG_FILE=%WINDIR%\system\dea.log

    if exist %REG_LOG_FILE% (set OPTION=OFF) else set OPTION=ON

    if [%1] neq [] (
        if /i [%1] neq [ON] (
            if /i [%1] neq [OFF] (
                if /i [%1] neq [/np] (
                    goto HELP
                )
            )else set OPTION=OFF
        )else set OPTION=ON

    )

    if /i [%2] neq [] (
        if /i [%2] neq [/np] goto HELP      &rem do not pause
    )

:BEGIN
    if exist %REG_FILE% del %REG_FILE% /F/Q

    if /i %OPTION% equ ON (
        echo Windows Registry Editor Version 5.00 >%REG_FILE%
        echo [HKEY_CURRENT_USER\Software\Microsoft\Command Processor]>>%REG_FILE%
        echo "DelayedExpansion"=dword:00000001>>%REG_FILE%
        echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Command Processor]>>%REG_FILE%
        echo "DelayedExpansion"=dword:00000001>>%REG_FILE%

        echo Delay Extensions OPTION=%OPTION% > %REG_LOG_FILE%
        date /t >>%REG_LOG_FILE% &time /t >>%REG_LOG_FILE%
    ) else (
        echo Windows Registry Editor Version 5.00 >%REG_FILE%
        echo [HKEY_CURRENT_USER\Software\Microsoft\Command Processor]>>%REG_FILE%
        echo "DelayedExpansion"=- >>%REG_FILE%
        echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Command Processor]>>%REG_FILE%
        echo "DelayedExpansion"=- >>%REG_FILE%
        if exist %REG_LOG_FILE% del %REG_LOG_FILE% /F/Q
    )

    regedit /s %REG_FILE%
    if exist %REG_FILE% del %REG_FILE% /F/Q

    echo Delay Extensions OPTION = %OPTION%
    echo Register success.
    )

    if /i [%1] equ [/np] goto END
    if /i [%2] equ [/np] goto END
    pause
    goto END

:HELP
    echo denf.bat - to set DelayedExpansion option on or off
    echo Usage denf.bat [[on]/[off]] [/np]
    echo on  - switch DelayedExpansion to on
    echo off - switch DelayedExpansion to off
    echo /np - do not pause when finished.
    echo if no paramters, switch between on/off

:END
endlocal
@echo on

 