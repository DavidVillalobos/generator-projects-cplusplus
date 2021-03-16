/* 
    File: generateClass.py
    Version: 2.0.0
    Date: 16-03-2021 
    Author: David Villalobos
    Description: With this file you can 
    generate c++ classes implementing 
    gets and sets in addition to the 
    constructor and destructor.
    You can use it from the console 
    by sending arguments and the interactive console
*/
#include<iostream>
#include<map>
#include<fstream>
#include<tuple>
#include<list>
#include<sstream>
#include<algorithm>

#define VERSION "GenClassC++ V2.0.0"

std::map<std::string, std::string> Types = {
	{"int", "0"},{"char", "\"\""},{"float", "0.0"},
	{"double", "0.0"},{"string", "\"\""},{"bool", "false"}
};

std::string help(){
    std::stringstream s;
    s << "[Generator of classes for C++]";
    s << "Author: https://github.com/DavidVillalobos";
    s << "Usages:";
    s << "* Interactive console";
    s << "    generateClass";
    s << "* Through arguments";
    s << "    generateClass [name_class] [type_attribute_1] [name_attribute_1] ...";
    return s.str();
}

std::string checkIncludes(std::list<std::tuple<std::string,std::string>> &attributes){
    std::stringstream includes;
    bool using_string = false;
    std::string type;
    for(auto attr : attributes){
        type = std::get<0>(attr);
        if (type == "string" || type == "std::string"){ 
            using_string = true;
        } else if(Types[type] == ""){  // attribute as c++ class 
            type.erase(remove(type.begin(), type.end(),'*'),type.end()); 
            includes << "#include\"" + type + "\"\n";
        }  
    }
    if(using_string){
        includes << "#include<string>\nusing namespace std;\n";
    }
    return includes.str();
}

std::string generate_attributes(std::list<std::tuple<std::string,std::string>> &attributes){
    std::stringstream r;
    for (auto attr : attributes){
        r << '\t' << std::get<0>(attr) << ' ' << std::get<1>(attr) << '\n';
    }
    return r.str();
}

std::string generate_gets(std::list<std::tuple<std::string,std::string>> &attributes, std::string name_class
, bool prototype = false, bool offline = false){
    std::stringstream gets;
    std::string name_capitalize;
    if(prototype){
        for (auto attr : attributes){
            name_capitalize = std::get<1>(attr);
            name_capitalize[0] = toupper(name_capitalize[0]); // Upper Firt char
            gets << '\t' << std::get<0>(attr) << "get" << name_capitalize << "();\n";
        } 
    }else { 
        std::string space = "";
        if(!offline){ space = "\t"; }
        else { name_class += "::"; }
        for (auto attr : attributes){
            name_capitalize = std::get<1>(attr);
            name_capitalize[0] = toupper(name_capitalize[0]); // Upper Firt char
            gets << space << std::get<0>(attr) << ' ' << name_class << "get" << name_capitalize << "(){\n";
            gets << space << "\treturn " << std::get<0>(attr) << '\n';
            gets << space << "}\n"; 
        }
    }
    return gets.str();
}
 
std::string generate_sets(std::list<std::tuple<std::string,std::string>> &attributes, std::string name_class
, bool prototype = false, bool offline = false){
    std::stringstream sets;
    std::string name_capitalize;
    if(prototype){ 
        for (auto attr : attributes){
            name_capitalize = std::get<1>(attr);
            name_capitalize[0] = toupper(name_capitalize[0]); // Upper Firt char
            sets << "\tvoid set"<<name_capitalize<<"(" << std::get<0>(attr) << " " << std::get<0>(attr) <<");\n"; 
        }
    }else{ 
        std::string space = "";
        if(!offline){ space = "\t";}
        else { name_class += "::"; }
        for (auto attr : attributes){
            name_capitalize = std::get<1>(attr);
            name_capitalize[0] = toupper(name_capitalize[0]); // Upper Firt char
            sets << space << "void " << name_class << "set" << name_capitalize << '(' << std::get<0>(attr) << ' ' << std::get<1>(attr) << "){\n";
            sets << '\t' << space << "this->" << std::get<1>(attr) << " = " << std::get<1>(attr) << ";\n";
            sets << space << "}\n"; 
        }    
    }
    return sets.str();
}
/*
std::string generate_constructor(attributes, std::string name_class
, bool prototype = false, bool overloaded = false, bool offline = false){
    std::stringstream builder;
    if(prototype){
        builder << '\t';    
        if(overloaded){
            builder << name_class << '(';
            for (auto attr : attributes){
                builder << std::get<0>(attr) << ' ' <<  std::get<1>(attr) << " = ";
                builder << ((Types[std::get<0>(attr)) != "")? Types[std::get<0>(attr)] : "nullptr" );
                if(i < attributes.size() - 1){ builder << ", "; } 
            }
        }else{
            space = ""
            if offline: space = "\t"
            builder += name_class + "();\n" # without parameters
            builder += space + name_class + "(" # with parameters
            for i in range(len(attributes)):
                builder += "%s %s" % (attributes[i][0], attributes[i][1])
                if i < len(attributes) - 1: builder += ", "
        }
        builder += ");\n";
    }else{
        if overloaded:
            space = ""
            if not offline: space = "\t"
            builder += (name_class + "::" if offline else "\t") + name_class + "("
            builder_body = ""
            for i in range(len(attributes)):
                builder += "%s %s" % (attributes[i][0], attributes[i][1])
                if not offline: builder += " = " + (Types.get(attributes[i][0]) if Types.get(attributes[i][0]) != None else "nullptr")
                if i < len(attributes) - 1: builder += ", "
                builder_body += space + "\tthis->%s = %s;\n" % (attributes[i][1], attributes[i][1])
            if not offline: builder_body += "\t"
        else:
            space = ""
            if not offline: space = "\t"# builder without parameters
            builder = (name_class + "::" if offline else "\t") + name_class + "(){\n"
            for i in range(len(attributes)): 
                builder += space + "\tthis->%s = %s;\n" % (attributes[i][1], (Types.get(attributes[i][0]) if Types.get(attributes[i][0]) != None else "nullptr"))
            if not offline: builder += "\t"
            builder +="}\n";# builder with parameters
            builder += (name_class + "::" if offline else "\t") + name_class + "("
            builder_body = ""
            for i in range(len(attributes)): 
                builder += "%s %s" % (attributes[i][0], attributes[i][1])
                if i < len(attributes) - 1: builder += ", "
                builder_body += space + "\tthis->%s = %s;\n" % (attributes[i][1], attributes[i][1])
            if not offline: builder_body += "\t"
        builder += "){\n" + builder_body + "}\n";
    }
    return builder
}
*/

std::string generate_destructor(std::string name_class, bool prototype = false, bool offline = false){
    if(prototype){
        return "\t~" + name_class + "();\n";
    } 
    std::string space, scope = name_class;
    if(!offline){ space = "\t"; }
    else { scope += "::"; }
    return scope + "~" + name_class + "(){\n" + space + "}\n";
    
}

std::string toUpper(std::string word){
    for (int i = 0; i < int(word.length()); i++){
        word[i] = toupper(word[i]);
    }
    return word;
}

std::string generate_class(std::string name_class, std::list<std::tuple<std::string,std::string>> &attributes
, bool offline = false, bool builder_overloaded = false){
    std::stringstream declaration;
    declaration << "#ifndef " << toUpper(name_class) << "_H\n#define " << toUpper(name_class) << "_H\n";
    declaration << checkIncludes(attributes);
    declaration << "class "<< name_class << " {\n";
    declaration << "private:\n";
    declaration << generate_attributes(attributes);
    declaration << "public:\n";
    declaration << generate_constructor(attributes, name_class, offline, builder_overloaded, offline);
    declaration << generate_gets(attributes, name_class, offline, offline);
    declaration << generate_sets(attributes, name_class, offline, offline);
    declaration << generate_destructor(name_class, offline, offline);
    declaration << "};\n";
    declaration << "#endif //!" << toUpper(name_class) << "_H \n\n";
    std::string path = std::string(getenv("userprofile")) + "\\Desktop\\" + name_class;
    std::ofstream h_file(path + ".h");
    h_file << declaration.str();
    h_file.close();
    if(offline){
        std::stringstream implementation;
        implementation << "#include\"" << name_class << ".h\"\n\n";
        implementation << generate_constructor(attributes, name_class, false, builder_overloaded, true);
        implementation << generate_gets(attributes, name_class, false, offline);
        implementation << generate_sets(attributes, name_class, false, offline);
        implementation << generate_destructor(name_class, false, offline);
        std::ofstream cpp_file(path + ".cpp");
        cpp_file << implementation.str();
        cpp_file.close();
        declaration << implementation.str();
    }
    return declaration.str();
}


int main(int argc, char** argv){
    std::stringstream output;
    if(argc > 1){
        if(std::string(argv[1]) == "--help" || std::string(argv[1]) == "-help" || std::string(argv[1]) == "-h"){ 
            output << help();
        }else if(std::string(argv[1]) == "--version" || std::string(argv[1]) == "-version" || std::string(argv[1]) == "-v"){
            output << VERSION;
        }else if(argc > 3){
            std::list<std::tuple<std::string, std::string>> attributes;
            for (int i = 2; i < argc; i+=2){
                attributes.push_back(std::make_tuple(std::string(argv[i]),std::string(argv[i])));
            }
            output << "\nThe result of the class is as follows\n\n";
            output << generate_class(std::string(argv[1]), attributes, true, false);
        }else{
            output << "Error: Not give anyone atribute for class " << argv[1];
        }
    }else{
        std::cout << "Creating c++ class with console interactive";
        std::list<std::tuple<std::string, std::string>> attributes;
        std::string name_class;        
        std::cout << "Name class:";
        getline(std::cin, name_class);
        std::string type, name, answer;
        while(true){
            std::cout << "Create a new variable (Y/n):";
            getline(std::cin, answer);
            if(answer == "n"){ break; }
            std::cout << "Type: ";
            getline(std::cin, type);
            std::cout << "Name: ";
            getline(std::cin, name);
            attributes.push_back(std::make_tuple(type,name));
        };
        bool overloaded, offline;
        std::cout << "Generate builder overloaded (Y/n):";
        getline(std::cin, answer);
        overloaded = answer != "n";

        std::cout << "Generate class inline (Y/n):";
        getline(std::cin, answer);
        offline = answer != "n";

        output << "\nThe result of the class is as follows\n\n";
        output << generate_class(name_class, attributes, offline, overloaded);
    }
    std::cout << output.str();
}