@ECHO OFF
REM File: run.bat
REM Version: 1.0.0
REM Date: 17-03-2021 
REM Author: David Villalobos
REM Description: start project

IF NOT EXIST build ( build )
start build/genc++