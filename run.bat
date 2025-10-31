@echo off
echo Compiling Piano App...
clang++ src/main_music.cpp src/piano_core.cpp src/recording.cpp src/playback.cpp src/file_io.cpp src/state_management.cpp src/gui_logic.cpp src/gui.cpp -l SplashKit -o piano

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful! Running...
    piano.exe
) else (
    echo Compilation failed!
    pause
)