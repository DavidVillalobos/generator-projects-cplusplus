@ECHO off
REM File: init.bat
REM Author: David Villalobos Gonzalez
REM Date: 01-06-2021

REM Size console
mode con: cols=100 lines=25 
REM Title console
title Generate Projects C++ 

:Start
cls
ECHO.  + - - - - - - - - - - - - - - - +
ECHO. [93mGenerator of Classes for [96mC++[0m
ECHO.                                 
ECHO.   1. Create Class C++           
ECHO.   2. Create Makefile            
ECHO.   3. Exit                       
ECHO.  + - - - - - - - - - - - - - - - +

set choice=
set /p choice= Enter an option:
if not '%choice%'=='' set choice=%choice:~0,1%
if '%choice%'=='1' goto CreateClassC++
if '%choice%'=='2' goto CreateMakefile
if '%choice%'=='3' goto Exit
ECHO "%choice%" Opcion incorrecta.
pause
ECHO.
goto Start

:CreateClassC++
python "class_generator.py"
goto Start

:CreateMakefile
goto Start

:Exit
