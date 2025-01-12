@echo off
rem Compile all .cpp files in the current directory
g++ -std=c++17 *.cpp -o rummikub

rem Check if the compilation was successful
if %errorlevel%==0 (
    echo Build successful. Run rummikub.exe to execute.
) else (
    echo Build failed.
)
pause
