@ECHO OFF
ECHO Deleting all Eagle bakup files
PAUSE
DEL *.s#?
DEL *.b#?
DEL *.l#?
DEL *.job
Del *.pro
Del *.scr
Attrib -h *.*
Del *.lck
