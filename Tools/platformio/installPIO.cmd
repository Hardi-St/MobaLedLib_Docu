@echo off
powershell Invoke-WebRequest "https://raw.githubusercontent.com/Hardi-St/MobaLedLib_Docu/master/Tools/platformio/installPIO.ps1" -o:installPIO.ps1
powershell .\installPIO.ps1
path=%path%;%USERPROFILE%\.platformio\penv\Scripts
pause platformio installed
