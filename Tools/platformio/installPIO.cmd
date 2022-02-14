@echo off

:: Check for Python Installation
python --version >nul 2>NUL
if errorlevel 1 goto errorNoPython

powershell Invoke-WebRequest "https://raw.githubusercontent.com/Hardi-St/MobaLedLib_Docu/master/Tools/platformio/installPIO.ps1" -o:installPIO.ps1
if errorlevel 1 goto failed1
powershell .\installPIO.ps1
if errorlevel 1 goto failed2
path=%path%;%USERPROFILE%\.platformio\penv\Scripts
pause platformio installed

goto :eof


:errorNoPython
echo.
echo Error: Python not installed - please visit https://www.python.org/downloads/windows/
start https://www.python.org/downloads/windows/
goto :eof

:failed1
echo.
pause Download of installPIO.ps1 failed
goto :eof

:failed2
echo.
pause Execution of installPIO.ps1 failed
goto :eof
