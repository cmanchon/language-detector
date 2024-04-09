#include "text.hpp"
#include <dirent.h>
#define TEXTS_REP "data/"
#define ALL_LANGUAGES_FILE "all_languages.txt"
#ifndef PARSING_HPP
#define PARSING_HPP

void print_texts(const std::vector<Text> T, bool show_texts = 1);
std::vector<Text> parse_all_texts(bool set_rec_words=0, bool set_special_characters=0);

#endif