@echo off
setlocal
rem ---------------------------------------------------------------
rem  Exportiert alle Druckteile der Post-Station als STL (Front oben)
rem  Lege diese Datei in denselben Ordner wie post_packstation_h0.scad
rem  und starte sie per Doppelklick.
rem ---------------------------------------------------------------
set "OPENSCAD=C:\Program Files\OpenSCAD\openscad.exe"
set "SCAD=%~dp0post_packstation_h0.scad"
set "OUT=%~dp0stl"
rem Optional bei OpenSCAD 2024/2025 (viel schneller): Zeile unten aktivieren
rem set "EXTRA=--backend=manifold"
set "EXTRA="

if not exist "%OUT%" mkdir "%OUT%"

for %%P in (canopy front_core skin_yellow skin_white skin_black frame_base frame_walls back led_holder) do (
  echo == %%P
  "%OPENSCAD%" %EXTRA% -o "%OUT%\%%P.stl" -D "part=\"%%P\"" -D "print_layout=true" "%SCAD%"
)

echo.
echo Fertig: %OUT%
pause
