@echo off
REM newzy create

SET TO=*.csp
set FROM=*.htm

for /R %%D in (.) do (
    cd %%D
    cd
    ren %FROM% %TO%
)

pause