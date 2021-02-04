@echo off

set cppfiles=src/*.cpp src/ECS/*.cpp
set links=-I"C:\code\libs\SDL\64\include" -L"C:\code\libs\SDL\64\lib" -I"C:\juice\src" -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lws2_32 -Wl,-subsystem,windows

if [%1]==[] (
    g++.exe -std=c++17 %cppfiles% %links%  -o bin/dev/main.exe && CALL run.bat
) else (
    clang++ -std=c++17 --target=x86_64-w64-mingw32-g++ -fuse-ld=lld.exe -g -gcodeview -Wl,/debug,/pdb:bin/debug/debug.pdb -Wno-narrowing %cppfiles% %links% -o bin/debug/main.exe
)