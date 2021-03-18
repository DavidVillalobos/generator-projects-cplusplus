@ECHO OFF
REM File: run.bat
REM Version: 2.0.0
REM Date: 18-03-2021 
REM Author: David Villalobos
REM Description: run project and build if not exist

IF NOT EXIST build ( build ) 

cd build
REM start program
genc++
cd ..