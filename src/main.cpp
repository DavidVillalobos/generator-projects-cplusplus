/*
    File: main.cpp
    Version: 2.0.0
    Date: 15-03-2021 
    Author: David Villalobos
    Description: Main file contains the menu that allows 
    executing the necessary codes to create a project.
*/

#include<iostream>
#include<fstream>
#include <cstdlib>

int read_option();
void generate_main();

int main(){
    system("mode con: cols=100 lines=25");
    system("title Generator of Projects C++");
    while(true){
        system("cls");
        std::cout << " [0m+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - +\n";
        std::cout << "      [92m  ____                           _\n";
        std::cout << "       / ___| ___ _ __   ___ _ __ __ _| |_ ___  _ __\n";
        std::cout << "      | |  _ / _ \\ '_ \\ / _ \\ '__/ _` | __/ _ \\| '__|\n";
        std::cout << "      | |_| |  __/ | | |  __/ | | (_| | || (_) | |\n";
        std::cout << "       \\____|\\___|_| |_|\\___|_|  \\__,_|\\__\\___/|_|\n";
        std::cout << "   ____            _           _          [91m____[92m\n";
        std::cout << "  |  _ \\ _ __ ___ (_) ___  ___| |_ ___   [91m/ ___| _     _[92m\n";
        std::cout << "  | |_) | '__/ _ \\| |/ _ \\/ __| __/ __| [91m| |   _| |_ _| |_[92m\n";
        std::cout << "  |  __/| | | (_) | |  __/ (__| |_\\__ \\ [91m| |__|_   _|_   _|[92m\n";
        std::cout << "  |_|   |_|  \\___// |\\___|\\___|\\__|___/  [91m\\____||_|   |_|[92m\n";
        std::cout << "                |__/\n";
        std::cout << "   Author: https://github.com/DavidVillalobos \n";
        std::cout << " [0m+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - +\n";
        std::cout << "   1. [94mCreate Class[0m\n";
        std::cout << "   2. [94mCreate Makefile[0m\n";      
        std::cout << "   3. [94mCreate Main[0m\n";
        std::cout << "   4. [91mExit\n"; 
        std::cout << " [0m+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - +\n";
        std::cout << "   Enter an option : ";
        switch(read_option()){
            case 1: system("class_generator"); break;
            case 2: system("makefile_generator"); break;
            case 3: generate_main(); break;
            case 4: return 0;
            default: std::cout << "Option wrong."; break;
        }
    }
}

// validate for cin integer
int read_option(){
    int option;
    while(true){
        if(std::cin>>option){
            return option;
        }else{
            std::cin.clear();
	        std::cin.ignore(1024, '\n');
            std::cout<<"The option must be integer";
        }
    }
}

// generator of main
void generate_main(){
    std::string name;
    std::cout<<"File name: ";
    std::cin>>name; 
    if (name.find(".cpp") == std::string::npos) { // not find .cpp
        name += ".cpp";
    }
    std::string path = std::string(getenv("userprofile")) + "\\Desktop\\" + name;
    std::ofstream file(path);      
    file << "#include<iostream>\n";
    file << "using namespace std;\n\n";
    file << "int main(int argc, char** argv){\n";
    file << "\tcout << \"Hello World\" << endl;\n";
    file << "}\n";
    file.close();
    std::cout << "Your file is ready -> " + path + '\n';
    system("pause");
}