#include "../include/text.hpp"


int is_in(const std::string s, char c){
    for (int i = 0 ; i < (int)s.size() ; i++){
        if (s[i] == c)
            return i;
    }

    return -1;
}

int is_in(std::vector<std::string> V, std::string S){
    for (int i = 0 ; i < (int)V.size() ; i++){
        if (V[i] == S)
            return i;
    }
    return -1;
}

bool is_int(const std::string s){
    return std::regex_match(s, std::regex("[+-]?[0-9]+"));
}

bool is_float(const std::string s){
    return std::regex_match(s, std::regex("[+-]?[0-9]+[.]?[0-9]+"));
}


bool strcmp_case_insensitive(const std::string s1, const std::string s2){
    std::string s1tmp(s1);
    std::string s2tmp(s2);
    std::transform(s1tmp.begin(), s1tmp.end(), s1tmp.begin(), ::tolower);
    std::transform(s2tmp.begin(), s2tmp.end(), s2tmp.begin(), ::tolower);

    return s1tmp == s2tmp;
}




//TEXT CLASS

Text::Text(std::string filename){
    std::ifstream file(filename);

    if (!file.is_open()){
        std::cerr << "error Text::Text(std::string filename) : error opening file" << filename <<"\n";
        exit(1);
    }

    //Open the all_languages which stores all registered languages
    std::vector<std::string> all_languages;
    std::ifstream file_languages("data/all_languages.txt");

    if (!file_languages.is_open()){
        std::cerr << "error Text::Text(std::string filename) : error opening file all_languages.txt\n";
        exit(1);
    }

    std::string buf;
    while (file_languages.peek() != std::ifstream::traits_type::eof()){
        file_languages >> buf;
        all_languages.push_back(buf);
    }



    file.seekg(0);

    //Check if file is data -> if it has a language name as the first word
    file >> buf;
    if (is_in(all_languages, buf) != -1)
        language = buf;
    else
        text.push_back(buf);


    while (file.peek() != std::ifstream::traits_type::eof()){
        file >> buf;
        text.push_back(buf);
    }
}

void Text::print() const{
    std::cout << BOLD << "Language: " << END_FORMAT << language << BOLD << "\n\nSize: " << END_FORMAT << text.size();
    if (text.size() > 1)
        std::cout << " words.";
    else
        std::cout << " word, " << text[0].size() << "characters";
    std::cout << BOLD << "\n\nContent: \n" << END_FORMAT;
    for (int i = 0 ; i < (int) text.size() ; i++){
        std::cout << text[i] << " ";
    }
    std::cout << "\n";

    if (special_characters.size() > 0){
        std::cout << BOLD << "\nSpecial characters: '" << END_FORMAT << special_characters << "'"; 
        
        std::cout << "\n";
    }

    if (rec_words.size() > 0){
        std::cout << BOLD << "\nRecognizable words: " << END_FORMAT << "\n"; 
        for (int i = 0 ; i < (int)rec_words.size() ; i++){
            std::cout << rec_words[i];
            if (i < (int)rec_words.size()-1)
                std::cout << ", ";
        }
        std::cout << "\n";
    }
}


template <typename ONE_CHARACTER> 
int Text::is_in_text(ONE_CHARACTER c) const{
    if (!std::is_same<ONE_CHARACTER, std::string>::value && !std::is_same<ONE_CHARACTER, char>::value){
        std::cerr << "error is_in_text(): parameter is not std::string nor charn";
        exit(EXIT_FAILURE);
    }
    
    int ind;
    for (int i = 0 ; i < (int)text.size() ; i++){
        ind = text[i].find(c);
        if (ind != std::string::npos)
            return ind;
    }

    return -1;
}

template <typename ONE_CHARACTER> 
int Text::is_in_special_characters(ONE_CHARACTER c) const{
    if (!std::is_same<ONE_CHARACTER, std::string>::value && !std::is_same<ONE_CHARACTER, char>::value){
        std::cerr << "error is_in_special_characters(): parameter is not std::string nor char\n";
        exit(EXIT_FAILURE);
    }
    
    int ind = special_characters.find(c);
    if (ind != (int)std::string::npos)
        return ind;

    return -1;
}


void Text::set_special_characters(){
    std::string normal_characters = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ-*+/',.:0123456789()«»?!";

    for (int i = 0 ; i < (int)text.size() ; i++){
        for (int j = 0 ; j < (int)text[i].size() ; j++){
            if (is_in_special_characters(text[i][j]) == -1 && normal_characters.find(text[i][j]) == std::string::npos){
                if (special_characters.size() == 0 || j == 0)
                    special_characters.append(text[i], j, 2);
                else
                    special_characters.append(text[i], j-1, 2);
                // special_characters.push_back(' ');
                j++;
            }

        }
    }
}


void Text::set_rec_words(){
    std::vector<int> occurences;
    std::string tmp;
    int ind;

    for (int i = 0 ; i < (int)text.size() ; i++){

        if (is_int(text[i]) || is_float(text[i]))
            continue;
        
        tmp = text[i];
        std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
        tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ispunct), tmp.end());

        ind = is_in_rec_words(tmp);
        if (ind == -1){
            //new word
            rec_words.push_back(tmp);
            occurences.push_back(1);
        }
        else{
            occurences[ind]++;
        }

    }
    // We have all words saved in rec_words.
    
    // We now have to get rid of rarely used words.

    // Delete below a certain number:
    // for (int i = 0 ; i < (int)rec_words.size() ; i++){
    //     if (occurences[i] <= (int)rec_words.size()/10){
    //         rec_words.erase(rec_words.begin() + i);
    //         occurences.erase(occurences.begin() + i);

    //     }
    // }

    // Delete in order to get a maximum of 14 words:
    int delete_below = 1;
    while (rec_words.size() > 15)    {
        for (int i = 0 ; i < (int)rec_words.size() ; i++){
            if (occurences[i] <= delete_below){
                rec_words.erase(rec_words.begin() + i);
                occurences.erase(occurences.begin() + i);

            }
        }
        delete_below++;
    }
    


}


void Text::find_language(std::vector<Text> texts){
    if (!language.empty()){
        std::cout << "This text's language was already found, it's " << language << ".\n";
        return;
    }

    if (texts.empty()){
        std::cerr << "error find_languages(): texts is empty!\n";
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> possible_languages; 
    std::vector<int> occurences_char;
    std::vector<int> occurences_word;
    std::vector<int> frequency;

    //1st method: recognize the text's special characters
    if (special_characters.empty())
        set_special_characters();

    int ind;
    std::string buf;
    for (int i = 0 ; i < (int)texts.size() ; i++){
        occurences_char.push_back(0);

        if (texts[i].get_language().empty())
            continue;
        
        if (texts[i].get_special_characters().empty())
            texts[i].set_special_characters();


        for (int j = 0 ; j < (int)texts[i].get_special_characters().size() ; j+=2){
            
            buf.append(texts[i].get_special_characters(), j, 2);
            ind = is_in_special_characters(buf);
            buf.clear();
            if (ind != -1){
                //one character in common
                if (is_in(possible_languages, texts[i].get_language()) == -1)
                    possible_languages.push_back(texts[i].get_language());

                occurences_char[i]++;
            }

        }
    }
    
    if (!possible_languages.empty())
        language.assign(possible_languages[0]);

    if (possible_languages.size() != 1){
        // Multiple possibilities found using symbols
        // 2nd method: recognize the texts most used words

        if (rec_words.empty())
            set_rec_words();

        for (int i = 0 ; i < (int)texts.size() ; i++){
            occurences_word.push_back(0);
            if (texts[i].get_language().empty())
                continue;
            
            if (texts[i].get_rec_words().empty())
                texts[i].set_rec_words();


            for (int j = 0 ; j < (int)texts[i].get_rec_words().size() ; j++){
                
                ind = is_in_rec_words(texts[i].get_rec_words()[j]);
                if (ind != -1){
                    //one character in common
                    if (is_in(possible_languages, texts[i].get_language()) == -1)
                        possible_languages.push_back(texts[i].get_language());

                    occurences_word[i]++;
                }

            }
        }


        if (possible_languages.empty()){
            std::cout << "No language was found for this text.\n";
            return;
        }


        if (possible_languages.size() == 1){
            language = possible_languages[0];
            return;
        }

        //Find highest occurence
        // - symbol
        int max_char = 0, max_ind_char;
        for (int i = 0 ; i < (int)occurences_char.size() ; i++){
            if (occurences_char[i] > max_char){
                max_char = occurences_char[i];
                max_ind_char = i;
            }
        }

        // - word
        int max_word = 0, max_ind_word;
        for (int i = 0 ; i < (int)occurences_word.size() ; i++){
            if (occurences_word[i] > max_word){
                max_word = occurences_word[i];
                max_ind_word = i;
            }
        }

        //total
        int max = 0, max_ind;
        for (int i = 0 ; i < (int)occurences_word.size() ; i++){
            frequency.push_back(occurences_char[i]+occurences_word[i]);
            if (frequency[i] > max){
                max = frequency[i];
                max_ind = i;
            }
        }

        std::cout << "Multiple languages were found: ";
        for (int i = 0 ; i < (int)possible_languages.size() ; i++){
            std::cout << possible_languages[i];
            if (i < (int)possible_languages.size()-1)
                std::cout << ", ";
        }

        std::cout << "\nSpecial characters: " << max_char << " in common with " << texts[max_ind_char].get_language();
        std::cout << "\nRecognizable words: " << max_word << " in common with " << texts[max_ind_word].get_language();

        language.assign(texts[max_ind].get_language());
        std::cout << "\nWe found the highest number of similarities with " << language;
    }
    std::cout << "\n";

    return;
}