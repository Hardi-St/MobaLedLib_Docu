@echo off

SET LIB_PATH=%USERPROFILE%\Documents\arduino\libraries

for /R "%LIB_PATH%\MobaLedLib\examples\" %%i in (*.ino) do (
    if "%1"=="" (
        find /c "%%~ni" ExcludeAVRProjects.txt >nul:
        if errorlevel 1 (
            echo Building %%i
            call BuildAvr.cmd "%%i"
            if errorlevel 1 (
                echo AVR Build failed for %%i
                pause
            )
        )
    )
    find /c "%%~ni" ExcludeESPProjects.txt >nul:
    if errorlevel 1 (
        echo Building %%i
        call BuildESP.cmd "%%i"
        if errorlevel 1 (
            echo ESP32 Build failed for %%i
            pause
        )
    )
)
