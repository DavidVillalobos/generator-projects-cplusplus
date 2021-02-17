""" 
    File: main_generator.py 
    Version: 1.0.1
    Date: 10-02-2021    
    Author: David Villalobos
    Description: This file generate main 
"""
import sys
import os

if __name__ == '__main__':
    name = ''
    if len(sys.argv) > 1: name = sys.argv[1]
    name = input('File name: ')
    path = os.getenv('userprofile') + "\\Desktop\\" + name + '.cpp'
    with open (path, 'w') as file:      
        file.write("#include<iostream>\n")
        file.write("using namespace std;\n\n")
        file.write("int main(int argc, char** argv){\n")
        file.write("\tcout << \"Hello World\" << endl;\n")
        file.write("}\n")
    file.close()
    print('Your file is ready -> ' + name + '.cpp')