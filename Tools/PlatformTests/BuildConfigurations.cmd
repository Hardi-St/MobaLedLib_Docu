@echo off
SETLOCAL ENABLEDELAYEDEXPANSION

if "%1"=="AM328" goto ok
if "%1"=="ESP32" goto ok
if "%1"=="PICO" goto ok

echo Usage: %~n0 platform
echo.
echo Platform possible values are AM328 and ESP32
echo.
goto :eof

:ok
if exist FailedConfigurations.txt del FailedConfigurations.txt
SET LIB_PATH=%USERPROFILE%\Documents\arduino\libraries
SET SRC_PATH=%USERPROFILE%\Documents\arduino\MobaLedLib\Ver_3.1.0\LEDs_Autoprog

for /R ".\TestConfigurations\" %%i in (%1_Header_*.h) do (
    set doit=0
    if "%2"=="" set doit=1
    if "%2"=="%%~ni" set doit=1
    if "%2"=="%%~ni%%~xi" set doit=1
    if exist Exclude%1Configurations.txt (
        find /c "%%~ni" Exclude%1Configurations.txt >nul:
        if not errorlevel 1 set doit=0
    )
    
    if "!doit!"=="1" call :build %1 "%%i" 
)

if exist FailedConfigurations.txt (
    echo =============== failed Configurations ===================
    type FailedConfigurations.txt
    echo =========================================================
) else (
    echo All builds OK    
)
goto :eof

:build
copy %2 "%SRC_PATH%\LEDs_Autoprog.h" >nul:
cd "%SRC_PATH%"
echo Building %~n2
    call Start_%1_Sub.cmd noflash
    if errorlevel 1 (
        if "%1"=="ESP32" (
            echo x > "%aTemp%\rebuildFailed.txt"
            call Start_%1_Sub.cmd noflash
        )
        if errorlevel 1 (
            echo Build failed for %2 >>%~p0FailedConfigurations.txt
        )
    )
)
cd %~p0
goto :eof