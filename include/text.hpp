#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#ifndef TEXT_HPP
#define TEXT_HPP

#define BOLD "\033[1;37m"
#define END_FORMAT "\033[0m"

class Text{
    private:
        std::vector<std::string> text;
        std::string language;
        std::vector<std::string> rec_words;
        std::vector<std::string> special_caracters;

    public:
        Text(){};
        Text(std::string filename);
        ~Text(){};

        void print() const;
        bool is_in(std::string word) const;
};



#endif