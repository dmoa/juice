@echo off

set cppfiles=src/*.cpp src/ECS/*.cpp src/ECS/Animation/*.cpp src/utils/*.cpp

if [%1]==[] (
    g++.exe -std=c++17 src/*.cpp src/ECS/*.cpp src/ECS/Animation/*.cpp src/utils/*.cpp src/Globals/* -I"C:\dev\SDL\64\include" -L"C:\dev\SDL\64\lib" -I"C:\juice\src" -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lws2_32 -o bin/dev/main.exe -Wl,-subsystem,windows && CALL run.bat
) else (
    clang++ -std=c++17 --target=x86_64-w64-mingw32-g++ -fuse-ld=lld.exe -g -gcodeview -Wl,/debug,/pdb:bin/debug/debug.pdb -I"C:\dev\SDL\64\include" -L"C:\dev\SDL\64\lib" -I"C:\juice\src" -w -Wno-narrowing -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lws2_32 -Wl,-subsystem,windows -o bin/debug/main.exe %cppfiles%
)

::g++.exe -std=c++0x src/*.cpp src/ECS/*.cpp src/ECS/Animation/*.cpp src/utils/*.cpp src/Globals/* -I"C:\dev\SDL\64\include" -L"C:\dev\SDL\64\lib" -I"C:\juice\src" -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lws2_32 -o %output_dir% %extra% -Wl,-subsystem,windows && if [%1]==[] (CALL run.bat)

::clang++.exe -x c++ -std=c++11 src/*.cpp src/ECS/*.cpp src/ECS/Animation/*.cpp src/utils/*.cpp src/Globals/* -I"C:\dev\SDL\64\include" -L"C:\dev\SDL\64\lib" -I"C:\juice\src" -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lws2_32 -Wl,-subsystem,windows -o bin/dev/main.exe
