@ECHO OFF
Title Build Project
REM File: build.bat
REM Version: 1.0.0
REM Date: 17-03-2021 
REM Author: David Villalobos
REM Description: build project

IF EXIST build ( DEL /F/Q/S build > NUL ) ELSE ( MKDIR build )
ECHO Building project . . .
REM Generator of classes
g++ src/class_generator.cpp -o build/genclassc++
REM Generator of Makefiles
g++ src/makefile_generator.cpp -o build/genmakec++
REM Generator of Main and Generator of Mains
g++ src/main.cpp -o build/genc++
