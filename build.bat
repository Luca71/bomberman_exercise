clang.exe -o .\bin\my_bomberman.exe -Icore\include -I .\SDL2-2.0.20\include\ -L .\SDL2-2.0.20\lib\x64\ .\main\src\main.c .\core\src\*.c -Xlinker /subsystem:console -lSDL2main -lSDL2 -lshell32 -lws2_32 && .\bin\my_bomberman.exe