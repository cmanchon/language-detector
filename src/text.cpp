#include "../include/text.hpp"

Text::Text(std::string filename){
    std::ifstream file(filename);

    if (!file.is_open()){
        std::cerr << "error Text::Text(std::string filename) : error opening file" << filename <<"\n";
        exit(1);
    }

    file.seekg(0);

    file >> language;

    std::string buf;

    while (file.peek() != std::ifstream::traits_type::eof()){
        file >> buf;
        text.push_back(buf);
    }
}

void Text::print() const{
    std::cout << BOLD << "Language: " << END_FORMAT << language << BOLD << "\n\nSize: " << END_FORMAT << text.size() << " words";
    std::cout << BOLD << "\n\nContent: \n" << END_FORMAT;
    for (int i = 0 ; i < (int) text.size() ; i++){
        std::cout << text[i] << " ";
    }
    std::cout << "\n";
}