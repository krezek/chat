call "C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\Tools\VsDevCmd.bat"

midl /acf game.acf /env amd64 game.idl

xcopy /Y game.h ..\include\game.h
xcopy /Y game_s.c ..\src\game_s.c

xcopy /Y game.h ..\..\Client\include\game.h
xcopy /Y game_c.c ..\..\Client\src\game_c.c

pause