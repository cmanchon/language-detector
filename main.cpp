#include "include/text.hpp"


int main(void){

    std::vector<Text> texts;
    Text T("data/norwegian_IA.txt");
    T.set_rec_words();
    T.print();
    std::cout << "\n ----------------------------\n\n";
    Text T4("data/swedish_IA.txt");
    T4.set_rec_words();
    T4.print();
    std::cout << "\n ----------------------------\n\n";
    Text T2("data/english_IA.txt");
    T2.set_rec_words();
    T2.print();
    std::cout << "\n ----------------------------\n\n";
    Text T3("data/french_IA.txt");
    T3.set_rec_words();
    T3.print();
    texts.push_back(T);
    texts.push_back(T2);
    texts.push_back(T3);
    texts.push_back(T4);

    std::cout << "\n ----------------------------\n\n";
    Text to_guess("test.txt");
    to_guess.print();

    std::cout << "\n3 languages parsed.\n\n";
    std::cout<< "Finding language of test file...\n\n";
    to_guess.find_language(texts);
    to_guess.print();

    // T.set_special_characters();
    // T.print();

    return 0;
}