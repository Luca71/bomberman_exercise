clang.exe -o tests.exe -I.\include -I..\core\include -I..\SDL2-2.0.20\include\ -L ..\SDL2-2.0.20\lib\x64\ .\src\*.c ..\core\src\*.c -lSDL2main -lSDL2 -lws2_32 && tests.exe