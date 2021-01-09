@ECHO off
REM File: init.bat
REM Author: David Villalobos Gonzalez
REM Date: 09-01-2021

REM Size console
mode con: cols=100 lines=25 
REM Title console
title Generator of Projects C++ 

:Start
cls
ECHO.  + - - - - - - - - - - - - - - - +
ECHO.      Generator of projects [95mC++[0m
ECHO.                                 
ECHO.          1. [92mCreate Class[0m
ECHO.          2. [94mCreate Makefile[0m          
ECHO.          3. [91mExit                      
ECHO.  [0m+ - - - - - - - - - - - - - - - +

set choice=
set /p choice= Enter an option :
if not '%choice%'=='' set choice=%choice:~0,1%
if '%choice%'=='1' goto CreateClassC++
if '%choice%'=='2' goto CreateMakefile
if '%choice%'=='3' goto Exit
ECHO "%choice%" Option wrong.
pause
ECHO.
goto Start

:CreateClassC++
python "class_generator.py"
goto Start

:CreateMakefile
python "makefile_generator.py"
goto Start

:Exit
