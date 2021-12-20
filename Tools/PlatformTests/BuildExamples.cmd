@echo off

if "%1"=="AM328" goto ok
if "%1"=="ESP32" goto ok
if "%1"=="" goto ok

echo Usage: %~n0 [platform]
echo.
echo Platform is optional, possible values are AM328 and ESP32
echo.
goto :eof

:ok
if exist FailedProjects.txt del FailedProjects.txt
SET LIB_PATH=%USERPROFILE%\Documents\arduino\libraries

for /R "%LIB_PATH%\MobaLedLib\examples\" %%i in (*.ino) do (
    call :build "%1" AM328 "%%i"
    call :build "%1" ESP32 "%%i"
)

if exist FailedProjects.txt (
    echo =============== failed projects ===================
    type FailedProjects.txt
    echo ===================================================
) else (
    echo All builds OK    
)
goto :eof

:build
set doit=0
if "%1"=="""" set doit=1
if "%1"==""%2"" set doit=1
if "%doit%"=="0" goto :eof

set doit=0
if not exist Exclude%2Projects.txt (
    set doit=1
) else  (
    find /c "%~n3" Exclude%2Projects.txt >nul:
    if errorlevel 1 set doit=1
)
if "%doit%"=="1" (
    echo Building %2 %3
    call Build%2.cmd "%3"
    if errorlevel 1 (
        echo %2 Build failed for %3 >>FailedProjects.txt
    )
)
goto :eof