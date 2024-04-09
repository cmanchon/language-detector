#include "include/parsing.hpp"


int main(int argc, char const *argv[]){

    std::vector<Text> T = parse_all_texts(1, 1);
    print_texts(T, 0);

    std::cout << "\n ----------------------------\n\n";

    std::string buf;
    std::cout << "\n\n\nText to guess:\n";
    while (std::getline(std::cin, buf, '\n') && buf != "Q"){
        std::cout << "\n\n\n";
    
        Text tmp_text;
        tmp_text.set_text(buf);
        tmp_text.find_language(T);
        tmp_text.print();
        std::cout << "\n\n\nText to guess:\n";
    }

    return 0;
}