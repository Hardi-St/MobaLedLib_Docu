@ECHO OFF
REM Fuses: Brown out Detection level 2.7V, 8MHz, Preserve EEPROM
SET lfuse=E2
SET hfuse=D5

SET ProgDir=C:\Program Files (x86)\Arduino\hardware\tools\avr

if "%Port%" == "" (
  REM User Input
  ECHO The COM port number could be found in the Arduino IDE
  set /p Port=Enter the COM Port Nr:
)

SET Cmd="%ProgDir%\bin\avrdude.exe" -C "%ProgDir%\etc\avrdude.conf" -p ATtiny85 -c stk500v1 -b19200 -P COM%Port%

IF NOT Exist "%ProgDir%\bin\avrdude.exe" (
  ECHO Error avrdude not found
  Goto :EOF
)

ECHO Writing the Fuses and programming the ATTiny
%Cmd% -U lfuse:w:0x%lfuse%:m -U hfuse:w:0x%hfuse%:m -U flash:w:ATTiny_Mini_Stepper.hex:i



