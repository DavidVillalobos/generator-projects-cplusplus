""" File: generateMakefiles.py
    Version: 1.0.0
    Date: 09-01-2021 
    Author: David Villalobos
    Description: With this file you can 
    generate makefiles for build C++ projects
"""

import sys
import os

def help():
    return  """ [Generator of Makefiles for C++]
    Author: https://github.com/DavidVillalobos
    Usages:
    * Interactive console
        makefile_generator.py
    * Through arguments
        makefile_generator.py [main] [out] [name_class_1] [name_class_2] ...
        """

def version(): return 'V1.0.0.'

def generate_makefile(main, classes, out, flags, targets):
    makefile = 'OBJS = ' + main + '.o ' + '.o '.join(classes) + '.o\n'
    makefile += 'SOURCE = ' + main + '.cpp\n'
    makefile += 'HEADER = ' + '.h '.join(classes) + '.h\n'
    makefile += 'OUT = ' + out + '.exe\n'
    makefile += 'CC = g++\n'
    makefile += 'FLAGS = -c ' 
    if flags['g']: 
        makefile += '-g '  
    if flags['Wall']: 
        makefile += '-Wall'   
    makefile += '\nLFLAGS =\n\n' 
    makefile += 'all: $(OBJS)\n'
    makefile += '\t$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)\n\n'
    makefile += main + '.o: ' + main + '.cpp\n'
    makefile += '\t$(CC) $(FLAGS) ' + main + '.cpp\n\n'
    for i in classes: 
        makefile += i + '.o: ' + i + '.cpp\n\t$(CC) $(FLAGS) ' + i + '.cpp\n\n'
    if targets['clean']: 
        makefile += 'clean:\n'
        makefile += '\tdel $(OBJS) $(OUT)\n\n'
    if targets['run']: 
        makefile += 'run: $(OUT)\n'
        makefile += '\t$(OUT)\n'
    path = os.getenv('DESKTOP') + "\\" + 'Makefile'
    with open (path, 'w') as file:
        file.write(makefile)
    file.close()
    return makefile

if __name__ == '__main__':
    output = ''
    if len(sys.argv) > 1:
        if sys.argv[1] == '--help' or sys.argv[1] == '-help' or sys.argv[1] == '-h': print(help())
        elif sys.argv[1] == '--version' or sys.argv[1] == '-version' or sys.argv[1] == '-v': print(version())
        elif len(sys.argv) > 2:
            print('Creating Makefile for c++ through arguments')
            main = sys.argv[1]
            out = sys.argv[2]
            classes = [ sys.argv[i] for i in range(3, len(sys.argv))]
            flags = {}
            flags['g'] = input('Allow debugging (Y/n):') != 'n'
            flags['Wall'] = input('Show all warnings (Y/n):') != 'n'
            targets = {}
            targets['clean'] = input('Include clean target (Y/n):') != 'n'
            targets['run'] = input('Include run target (Y/n):') != 'n'
            output = generate_makefile(main, classes, out, flags, targets)
            print("\nThe result of the makefile is as follows\n\n" + output)
        else:
            output += "Error: Not give anyone name for .exe "
    else:
        print('Creating Makefile for c++ with console interactive')
        classes = []
        main = input('Name Main: ')
        out = input('Name Out: ')
        while input('New class (Y/n):') != 'n': classes.append((input('Name: ')))
        flags = {}
        flags['g'] = input('Allow debugging (Y/n):') != 'n'
        flags['Wall'] = input('Show all warnings (Y/n):') != 'n'
        targets = {}
        targets['clean'] = input('Include clean target (Y/n):') != 'n'
        targets['run'] = input('Include run target (Y/n):') != 'n'
        output = generate_makefile(main, classes, out, flags, targets)
        print("\nThe result of the makefile is as follows\n\n" + output)
