@echo off

if "%1"=="AM328" goto ok
if "%1"=="ESP32" goto ok


echo Usage: %~n0 platform
echo.
echo Platform possible values are AM328 and ESP32
echo.
goto :eof

:ok
if exist FailedConfigurations.txt del FailedConfigurations.txt
SET LIB_PATH=%USERPROFILE%\Documents\arduino\libraries
SET SRC_PATH=%USERPROFILE%\Documents\arduino\MobaLedLib\Ver_3.1.0\LEDs_Autoprog

for /R ".\TestConfigurations\" %%i in (%1_*.h) do (
    call :build %1 "%%i" 
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
        echo Build failed for %2 >>%~p0FailedConfigurations.txt
    )
)
cd %~p0
goto :eof