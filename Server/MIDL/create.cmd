call "C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\Tools\VsDevCmd.bat"

midl /acf game.acf /env amd64 game.idl

copy game.h ..\include\game.h
copy game_s.c ..\src\game_s.c

copy game.h ..\..\Client\include\game.h
copy game_c.c ..\..\Client\src\game_c.c

pause