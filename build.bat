@ECHO OFF
REM File: build.bat
REM Version: 2.0.0
REM Date: 18-03-2021 
REM Author: David Villalobos
REM Description: build project

Title Build Project
mode con: cols=60 lines=8
color 02


ECHO Building project ...
IF EXIST build ( DEL /F/Q/S build > NUL ) ELSE ( MKDIR build )
ECHO Build generator of classes...
g++ src/class_generator.cpp -o build/genclassc++
ECHO Build generator of makefiles...
g++ src/makefile_generator.cpp -o build/genmakec++
ECHO Build Main...
g++ src/main.cpp -o build/genc++
ECHO Successful Build :D
timeout 4