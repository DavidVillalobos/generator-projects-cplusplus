"""
    File: main.py
    Version: 1.0.0
    Date: 21-01-2021 
    Author: David Villalobos
    Description: Main file contains the menu that allows 
    executing the necessary codes to create a project.
"""

import sys
import os

if __name__ == '__main__':
    os.system('mode con: cols=100 lines=25')
    os.system('title Generator of Projects C++')
    while(True):
        os.system('cls')
        print(' + - - - - - - - - - - - - - - - +          ')
        print('      Generator of projects [95mC++[0m')
        print('                                            ')
        print('          1. [92mCreate Class[0m      ')
        print('          2. [94mCreate Makefile[0m   ')      
        print('          3. [93mCreate Main[0m       ')  
        print('          4. [91mExit                    ') 
        print(' [0m+ - - - - - - - - - - - - - - - +   ')
        choice = input('Enter an option : ')
        if choice == '1':
            os.system('python "class_generator.py"')
        if choice == '2':
            os.system('python "makefile_generator.py"')
        if choice == '3':
            os.system('python "main_generator.py"')
        if choice == '4': break
        else: print('Option wrong.')
    