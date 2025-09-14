#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <unistd.h>
#include <algorithm>

std::string string_to_lower(std::string str){
    std::transform(
    str.begin(), str.end(), str.begin(),
    [](unsigned char c){return std::tolower(c);}
    );

    return str;
}


void search_files(std::string search_string, std::string searchpath, bool ignorecase){
    std::ifstream input_file;
    std::string line;
    std::string search_line;
    for(const auto & file : std::filesystem::directory_iterator(searchpath)){
        input_file.open(file.path());
        if(input_file.is_open()){
            while((getline(input_file, line))){
                if(ignorecase){
                    search_line = string_to_lower(line);
                } else{
                    search_line = line;
                }
                if(search_line.find(search_string) != std::string::npos){
                    std::cout << line << std::endl;
                }
            }
        } else {
            std::cerr << "Unable To Open File." << std::endl;

        }
        input_file.close();
    }
}

void search_output(std::string search_string, bool ignorecase){
    std::string input_line;
    std::string search_line;

    while(std::cin){
        getline(std::cin, input_line);

        if(ignorecase){
            search_line = string_to_lower(input_line);
        } else{
            search_line = input_line;
        }
        if(search_line.find(search_string) != std::string::npos){
            std::cout << input_line << std::endl;
        }
    }
}


int main(int argc, char **argv){
    bool ignorecase = false;

    std::string search_string;

    std::string search_path;
    int valid_argcount = 2;

    if(std::string("-i").find(argv[1]) != std::string::npos){
        ignorecase = true;
        search_string = string_to_lower(argv[2]);
        valid_argcount++;
    } else{
        search_string = argv[1];
    }
    if(!isatty(fileno(stdin))){
        search_output(search_string, ignorecase);
    } else if(argc >= valid_argcount){
        if(ignorecase){
            search_path = argv[3];
        } else{
            search_path = argv[2];
        }
        search_files(search_string, search_path, ignorecase);

    } else{
        std::cout << "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information." << std::endl;
    }

    std::cout << "End of code" << std::endl;
    return 0; 
} 
