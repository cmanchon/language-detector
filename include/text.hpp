#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <cctype>

#ifndef TEXT_HPP
#define TEXT_HPP

#define BOLD "\033[1;37m"
#define END_FORMAT "\033[0m"

int is_in(const std::string s, char c);
int is_in(std::vector<std::string> V, std::string S);
bool is_int(const std::string s);
bool is_float(const std::string s);
bool strcmp_case_insensitive(const std::string s1, const std::string s2);

class Text{
    private:
        std::string language;
        std::vector<std::string> text;
        std::vector<std::string> rec_words;
        std::string special_characters;

    public:
        Text(){};
        Text(std::string filename);
        ~Text(){};

        void print() const;
        std::string get_special_characters() const{return special_characters;};
        std::vector<std::string> get_rec_words() const{return rec_words;};
        std::string get_language() const{return language;};
        
        template <typename ONE_CHARACTER> 
        int is_in_text(ONE_CHARACTER) const;
        template <typename ONE_CHARACTER> 
        int is_in_special_characters(ONE_CHARACTER) const;
        int is_in_rec_words(std::string s)const{return is_in(rec_words, s);};

        void set_special_characters();
        void set_rec_words();
        void find_language(std::vector<Text> texts);
};




#endif