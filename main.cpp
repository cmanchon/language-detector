#include "include/parsing.hpp"


int main(int argc, char const *argv[]){

    // std::cout << "\n ----------------------------\n\n";
    // Text to_guess("test.txt");
    // to_guess.print();

    // std::cout << "\n3 languages parsed.\n\n";
    // std::cout<< "Finding language of test file...\n\n";
    // to_guess.find_language(texts);
    // to_guess.print();

    std::vector<Text> T = parse_all_texts(1, 1);
    print_texts(T, 0);

    std::cout << "\n ----------------------------\n\n";

    if (argc == 2){
        Text text_from_exe;
        text_from_exe.set_text(argv[1]);
        text_from_exe.find_language(T);
        text_from_exe.print();

    }
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