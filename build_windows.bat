@echo off
setlocal
if not exist bin mkdir bin

g++ -std=c++17 -Wall -Wextra -O2 -Iinclude src\main.cpp src\algorithms.cpp src\data.cpp -o bin\ai_learning_navigator.exe
if errorlevel 1 (
  echo.
  echo Kompilasi gagal. Pastikan g++ dari MinGW-w64 sudah terpasang dan ada di PATH.
  pause
  exit /b 1
)

echo Kompilasi berhasil: bin\ai_learning_navigator.exe
endlocal
pause