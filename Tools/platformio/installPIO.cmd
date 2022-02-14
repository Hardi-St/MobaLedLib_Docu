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
pause Error: Python not installed - please visit https://www.python.org/downloads/windows/
start https://www.python.org/downloads/windows/
exit 1

:failed1
echo.
pause Download of installPIO.ps1 failed
exit 1

:failed2
echo.
pause Execution of installPIO.ps1 failed
exit 1
