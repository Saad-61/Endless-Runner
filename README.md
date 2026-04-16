# Endless Runner (C++)

A Windows console endless runner game written in C++.

## Features
- Real-time lane movement with `W`, `A`, `S`, `D`
- Jump with `Space`
- Collect coins to increase score
- Increasing speed as distance grows
- Police chase after 500m
- Health/lives system and game-over screen
- Game history saved to local file with player name, score, and distance

## Controls
- `W`: Move up
- `A`: Move left
- `S`: Move down
- `D`: Move right
- `Space`: Jump

## Build And Run (Windows + MinGW g++)
```powershell
cd E:\work\LAB_PROJECT_PF
g++ Source.cpp -o endless_runner.exe
.\endless_runner.exe
```

## Files
- `Source.cpp`: Full game source code
- `Endless Runner Game History`: Local history file generated at runtime

## Notes
- This is a console game and uses Windows-specific headers (`windows.h`, `conio.h`).
- If `g++` is not recognized, install MinGW-w64 and add it to PATH.
