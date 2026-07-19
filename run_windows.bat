@echo off
if not exist bin\ai_learning_navigator.exe (
  echo Program belum dikompilasi. Jalankan build_windows.bat terlebih dahulu.
  pause
  exit /b 1
)
bin\ai_learning_navigator.exe
pause