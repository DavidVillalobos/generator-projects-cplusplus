""" File: generateClass.py
    Version: 1.0.2
    Date: 05-01-2021 
    Author: David Villalobos
    Description: With this file you can 
    generate c++ classes implementing 
    gets and sets in addition to the 
    constructor and destructor.
    You can use it from the console 
    by sending arguments and the interactive console
"""

import sys

Types = { 
	'int' : '0', 
	'char' : '\'\'', 
	'float': '0.0', 
	'double': '0.0', 
	'string' : '\"\"', 
	'bool' : 'false'
}

def help():
    return  """ [Generator of classes for C++]
    Author: https://github.com/DavidVillalobos
    Usages:
    * Interactive console
        generateClass.py
    * Through arguments
        generateClass.py [class] [name_class] [type_attribute_1] [name_attribute_1] ...
        """

def version(): return """V1.0.2"""
    
def checkIncludes(attributes):
    includes = ''
    using_string = False
    for attribute in attributes:
        if Types.get(attribute[0]) == None: 
            includes += '#include"%s.h"\n' % attribute[0].replace('*', '')
        elif attribute[0] == 'string' or attribute[0] == 'std::string': 
           using_string = True
    if using_string :
        includes += '#include<string>\nusing namespace std;\n'
    return includes
    
def generate_attributes(attributes):
    return ''.join(['\t%s %s;\n' % (i[0], i[1]) for i in attributes])
  
def generate_gets(attributes, name_class, prototype = False, offline = False):
    gets = ''
    if prototype:
        for i in attributes: gets += '\t%s get%s();\n' % (i[0], i[1].capitalize()) 
    else: 
        space = ''
        if not offline: space = '\t'
        for i in attributes:
            gets += '%s%s %sget%s(){\n%s\treturn %s;\n%s}\n' % (space, i[0], name_class + '::' if offline else '', i[1].capitalize(), space, i[1], space) 
    return gets
    
def generate_sets(attributes, name_class, prototype = False, offline = False):
    sets = ''
    if prototype: 
        for i in attributes:
            sets += '\tvoid set%s(%s %s);\n' % (i[1].capitalize(), i[0], i[1]) 
    else: 
        space = ''
        if not offline: space = '\t'
        for i in attributes:
            sets += '%svoid %sset%s(%s %s){\n' % (space, name_class + '::' if offline else '', i[1].capitalize(), i[0], i[1])
            sets += '\t%sthis->%s = %s;\n%s}\n' % (space, i[1], i[1], space) 
    return sets

def generate_constructor(attributes, name_class, prototype= False, overloaded = False, offline = False):
    builder = ''
    if prototype:
        builder += '\t'    
        if overloaded:
            builder += name_class + '('
            for i in range(len(attributes)):
                builder += '%s %s = ' % (attributes[i][0], attributes[i][1])
                builder += Types.get(attributes[i][0]) if (Types.get(attributes[i][0]) != None) else 'nullptr'
                if i < len(attributes) - 1: builder += ', '
        else:
            space = ''
            if offline: space = '\t'
            builder += name_class + '();\n' # without parameters
            builder += space + name_class + '(' # with parameters
            for i in range(len(attributes)):
                builder += '%s %s' % (attributes[i][0], attributes[i][1])
                if i < len(attributes) - 1: builder += ', '
        builder += ');\n';
    else:
        if overloaded:
            space = ''
            if not offline: space = '\t'
            builder += (name_class + '::' if offline else '\t') + name_class + '('
            builder_body = ''
            for i in range(len(attributes)):
                builder += '%s %s' % (attributes[i][0], attributes[i][1])
                if not offline: builder += ' = ' + (Types.get(attributes[i][0]) if Types.get(attributes[i][0]) != None else 'nullptr')
                if i < len(attributes) - 1: builder += ', '
                builder_body += space + '\tthis->%s = %s;\n' % (attributes[i][1], attributes[i][1])
            if not offline: builder_body += '\t'
        else:
            space = ''
            if not offline: space = '\t'# builder without parameters
            builder = (name_class + '::' if offline else '\t') + name_class + '(){\n'
            for i in range(len(attributes)): 
                builder += space + '\tthis->%s = %s;\n' % (attributes[i][1], (Types.get(attributes[i][0]) if Types.get(attributes[i][0]) != None else 'nullptr'))
            if not offline: builder += '\t'
            builder +='}\n';# builder with parameters
            builder += (name_class + '::' if offline else '\t') + name_class + '('
            builder_body = ''
            for i in range(len(attributes)): 
                builder += '%s %s' % (attributes[i][0], attributes[i][1])
                if i < len(attributes) - 1: builder += ', '
                builder_body += space + '\tthis->%s = %s;\n' % (attributes[i][1], attributes[i][1])
            if not offline: builder_body += '\t'
        builder += '){\n' + builder_body + '}\n';
    return builder
    
def generate_destructor(name_class, prototype = False, offline = False):
    if prototype: return '\t~%s();\n' % name_class
    else: return (name_class + '::' if offline else '\t') +'~%s(){\n%s}\n' % (name_class, '\t' if not offline else '')

def generate_class(name_class, attributes, offline = False, builder_overloaded = False):
    declaration = '#ifndef %s_H\n#define %s_H\n' % (name_class.upper(), name_class.upper())
    declaration += checkIncludes(attributes)
    declaration += 'class %s {\n' % name_class
    declaration += 'private:\n'
    declaration += generate_attributes(attributes)
    declaration += 'public:\n'
    declaration += generate_constructor(attributes, name_class, offline, builder_overloaded, offline)
    declaration += generate_gets(attributes, name_class, offline, offline)
    declaration += generate_sets(attributes, name_class, offline, offline)
    declaration += generate_destructor(name_class, offline, offline)
    declaration += '};\n'
    declaration += '#endif //!%s_H \n\n' % name_class.upper();
    with open ('%s.h' % name_class, 'w') as h_file:
        h_file.write(declaration)
    h_file.close()    
    if offline:
        implementation = '#include"%s.h"\n\n' % name_class
        implementation += generate_constructor(attributes, name_class, False, builder_overloaded, True)
        implementation += generate_gets(attributes, name_class, False, offline)
        implementation += generate_sets(attributes, name_class, False, offline)
        implementation += generate_destructor(name_class, False, offline)
        with open ('%s.cpp' % name_class, 'w') as cpp_file:
            cpp_file.write(implementation)
        cpp_file.close()
        declaration += implementation
    return declaration

if __name__ == '__main__':
    output = ''
    if len(sys.argv) > 1:
        if sys.argv[1] == '--help' or sys.argv[1] == '-help' or sys.argv[1] == '-h': print(help())
        elif sys.argv[1] == '--version' or sys.argv[1] == '-version' or sys.argv[1] == '-v': print(version())
        elif len(sys.argv) > 3:
            print('Creating c++ class through arguments')
            attributes = []
            for i in range(2, len(sys.argv), 2) : attributes.append((sys.argv[i], sys.argv[i+1]))
            overloaded = input('Generate builder overloaded (Y/n):') != 'n'
            offline = input('Generate class inline (Y/n):') == 'n'
            output += generate_class(sys.argv[1], attributes, offline, overloaded)
            print("\nThe result of the class is as follows\n\n" + output)
        else:
            output += "Error: Command or not give anyone atribute for class " + sys.argv[1]
    else:
        print('Creating c++ class with console interactive')
        attributes = []
        name_class = input('Name class: ')
        while input('Create a new variable (Y/n):') != 'n': attributes.append((input('Type: '), input('Name: ')))
        overloaded = input('Generate builder overloaded (Y/n):') != 'n'
        offline = input('Generate class inline (Y/n):') == 'n'
        output += generate_class(name_class, attributes, offline, overloaded)
        print("\nThe result of the class is as follows\n\n" + output)
