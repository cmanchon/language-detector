#include "../include/parsing.hpp"


void print_texts(const std::vector<Text> T, bool show_texts){
	std::cout << T.size() << " texts parsed:\n\n";
	for (int i = 0 ; i < (int)T.size() ; i++){
		T[i].print(show_texts);
		if (i < (int)T.size()-1)
			std::cout << "\n\n-------------------------------------------------------------------------------------\n\n";
	}
}


std::vector<Text> parse_all_texts(bool set_rec_words, bool set_special_characters){
	DIR * dh = opendir (TEXTS_REP);
	if (dh == NULL){
		std::cerr << "error parse_all_texts(): couldn't open " << TEXTS_REP << "\n";
		exit(EXIT_FAILURE);
	}

	std::vector<Text> res;
	struct dirent * dir_info = readdir(dh);
	char buf[256] = TEXTS_REP;
	
	while (dir_info != NULL){
		if (dir_info != NULL && dir_info->d_name[0] != '.' && strcmp(dir_info->d_name, ALL_LANGUAGES_FILE) != 0){
			memset((buf+sizeof(TEXTS_REP))-1, 0, 256-sizeof(TEXTS_REP));
			strcat(buf, dir_info->d_name);
			res.push_back((Text)(buf));
			if (set_rec_words)
				res[res.size()-1].set_rec_words();
			if (set_special_characters)
				res[res.size()-1].set_special_characters();
		}

		dir_info = readdir(dh);
	}

	closedir(dh);
	return res;
}
