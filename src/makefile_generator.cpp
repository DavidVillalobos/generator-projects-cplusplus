/*
    File: generateMakefiles.cpp
    Version: 2.0.0
    Date: 16-03-2021 
    Author: David Villalobos
    Description: With this file you can 
    generate makefiles for build C++ projects
*/
#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<list>

#define VERSION "GenMakeC++ V2.0.0"

// Get help like -h or -help
std::string help();

// Display a list elements like string concatenate with a separator 
std::string displayList(std::list<std::string> &list, std::string separator = " ");

// generate the targets to compile each file in list
std::string compileTargetFiles(std::list<std::string> list);

// generate the makefile according to main.cpp, classes.h out.exe, flags and library flags, clean and run target
std::string generate_makefile(std::string &main, std::list<std::string> &classes, 
std::string &out, std::string flags, std::string lflags, bool clean, bool run);

int main(int argc, char** argv){
    if (argc > 1){
        if(std::string(argv[1]) == "--help" || std::string(argv[1]) == "-help" || std::string(argv[1]) == "-h"){
            std::cout << help();
        } else if(std::string(argv[1]) == "--version" || std::string(argv[1]) == "-version" || std::string(argv[1]) == "-v"){
            std::cout << VERSION;
        } else if(argc > 2){
            std::string main = std::string(argv[1]);
            std::string out = std::string(argv[2]);
            std::list<std::string> classes;
            for (int i = 3; i < argc; i++){
                classes.push_back(std::string(argv[i]));
            }
            std::cout << "\nThe result of the makefile is as follows\n\n";
            std::cout << generate_makefile(main, classes, out, "-g -Wall", "", true, true);
        }else{
            std::cout << "Error: Not give anyone name for .exe ";
        }
    }else{
        std::cout << "Creating Makefile for c++ with console interactive\n";
        std::list<std::string> classes;
        std::cout << "Name Main: ";
        std::string main;
        getline(std::cin, main);
        if (main.find(".cpp") != std::string::npos) {
            main = main.substr(0, main.length() - 4);
        }
        std::cout << "Name Main is " << main << std::endl;
        std::cout << "Name Out: ";
        std::string out;
        getline(std::cin, out);
        if (out.find(".exe") != std::string::npos) {
            out = out.substr(0, out.length() - 4);
        }
        std::string name;
        std::string answer;
        while(true){
            std::cout << "New class (Y/n): ";
            getline(std::cin, answer);
            if(answer == "n"){ break; }
            std::cout << "Name: ";
            getline(std::cin, name);
            if (name.find(".h") != std::string::npos) {
                name = name.substr(0, name.length() - 2);
            }
            classes.push_back(name);
        };
        std::string flags = "";
        std::string lflags = ""; // library flags
        
        std::cout << "Allow debugging (Y/n):";
        getline(std::cin, answer);
        if(answer != "n") flags += "-g "; 
        
        std::cout << "Show all warnings (Y/n):";
        getline(std::cin, answer);
        if(answer != "n") flags += "-Wall ";
        
        std::cout << "Include clean target (Y/n):";
        getline(std::cin, answer);
        bool clean = answer != "n";
        
        std::cout << "Include run target (Y/n):";
        getline(std::cin, answer);
        bool run = answer != "n";
        
        std::cout << "\nThe result of the makefile is as follows\n\n";
        std::cout << generate_makefile(main, classes, out, flags, lflags, clean, run);
    }
}

std::string help(){
    std::stringstream s;
    s << "[Generator of Makefiles for C++]\n";
    s << "Author: https://github.com/DavidVillalobos \n"; 
    s << "Usages:\n"; 
    s << "* Interactive console \n"; 
    s << "    makefile_generator \n"; 
    s << "* Through arguments \n";  
    s << "    makefile_generator [main] [out] [name_class_1] [name_class_2] ...";
    return s.str();
}

std::string displayList(std::list<std::string> &list, std::string separator){
    std::stringstream r;
    for (auto i : list){
        r << i << separator;
    }
    return r.str();
}

std::string compileTargetFiles(std::list<std::string> list){
    std::stringstream r;
    for (auto i : list){
        r << i + ".o: " + i + ".cpp\n\t$(CC) $(FLAGS) " + i + ".cpp\n\n";
    }
    return r.str();
}

std::string generate_makefile(std::string &main, std::list<std::string> &classes, 
std::string &out, std::string flags, std::string lflags, bool clean, bool run){
    std::stringstream makefile;
    makefile << "OBJS = " + main + ".o " + displayList(classes, ".o ") + '\n';
    makefile << "SOURCE = " + main + ".cpp " + displayList(classes, ".cpp ") + '\n';
    makefile << "HEADER = " + displayList(classes, ".h ") + '\n';
    makefile << "OUT = " + out + ".exe\n";
    makefile << "CC = g++\n";
    makefile << "FLAGS = -c " + flags + '\n';
    makefile << "LFLAGS = " + lflags + "\n\n"; 
    makefile << "all: $(OBJS)\n";
    makefile << "\t$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)\n\n";
    makefile << main + ".o: " + main + ".cpp\n";
    makefile << "\t$(CC) $(FLAGS) " + main + ".cpp\n\n";
    makefile << compileTargetFiles(classes);
    if(clean){
        makefile << "clean:\n\tdel $(OBJS) $(OUT)\n\n";
    } 
    if(run){
        makefile << "run: $(OUT)\n\t$(OUT)\n";
    } 
    std::string path = std::string(getenv("userprofile")) + "\\Desktop\\Makefile";
    std::ofstream file(path);
    file << makefile.str();
    file.close();
    return makefile.str();
}