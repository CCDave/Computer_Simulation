#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <vector>
struct evl_token {
	enum token_type {NAME, NUMBER, SINGLE};

	token_type type;
	std::string str;
	int line_no;
};

typedef std::vector<evl_token> evl_tokens;

bool issingle(char ch){
	return (ch == '(') || (ch == ')') || (ch == '[') 
			|| (ch == ']') || (ch == ':') || (ch == ';') 
			|| (ch == ',');
}
bool isname(char ch){
	return isalpha(ch) || (ch == '_') || (ch == '\\') || (ch == '.');
}
bool extract_tokens_from_line(std::string line, int line_no, evl_tokens &tokens) { // use reference to modify it
	for (size_t i = 0; i < line.size();) {
		// comments
		if (line[i] == '/') {
			++i;
			if ((i == line.size()) || (line[i] != '/')) {
				std::cerr << "LINE " << line_no << ": a single / is not allowed" << std::endl;
				return false;
			}
			break; // skip the rest of the line by exiting the loop
		}

		// spaces
		else if (isspace(line[i]))
		{
			++i; // skip this space character
			continue; // skip the rest of the iteration
		}

		// SINGLE
		else if (issingle(line[i])) {
			evl_token token;
			token.line_no = line_no;
			token.type = evl_token::SINGLE;
			token.str = std::string(1, line[i]);
			tokens.push_back(token);
			++i;										// we consumed this character
			continue;									 // skip the rest of the iteration
		}

		// NAME
		else if (isname(line[i])) {
			size_t name_begin = i;
			for (++i; i < line.size(); ++i)
			{
				if (!(isname(line[i]) || isdigit(line[i]))) {
					break;
				}
			}
			evl_token token;
			token.line_no = line_no;
			token.type = evl_token::NAME;
			token.str = std::string(line.substr(name_begin, i-name_begin));
			tokens.push_back(token);
		}
			
		// NUMBER
		else if (isdigit(line[i])){
			size_t number_begin = i;
			for(++i; i < line.size(); ++i)
			{
				if (isname(line[i])){
					std::cerr << "LINE " << line_no << ": invalid character" << std::endl;
					return false;
				}
				else if (issingle(line[i]) || !((line[i]) || isname(line[i]))) {
					break;
				}
			}
			evl_token token;
			token.line_no = line_no;
			token.type = evl_token::NUMBER;
			token.str = std::string(line.substr(number_begin, i-number_begin));
			tokens.push_back(token);
		}
		else
		{
			std::cerr << "LINE " << line_no << ": invalid character" << std::endl;
			return false;
		}
	}
	return true;
}
bool extract_tokens_from_file(std::string file_name, evl_tokens &tokens) { // use reference to modify it
	std::ifstream input_file(file_name.c_str());
    if (!input_file){
        std::cerr << "I can't read " << file_name << "." << std::endl;
        return false;
    }
	tokens.clear();
	std::string line;
    for (int line_no = 1; std::getline(input_file, line); ++line_no){
		if (!extract_tokens_from_line(line, line_no, tokens)) {
			return false;
		}
	}
	return true;
}
void display_tokens(std::ostream &out, const evl_tokens &tokens) {
	for (size_t i = 0; i < tokens.size(); ++i) {
		if (tokens[i].type == evl_token::SINGLE) {
			out << "SINGLE " << tokens[i].str << std::endl;
		}
		else if (tokens[i].type == evl_token::NAME) {
			out << "NAME " << tokens[i].str << std::endl;
		}
		else if (tokens[i].type == evl_token::NUMBER) {
			out << "NUMBER " << tokens[i].str << std::endl;
		}
		else{
			out << "LINE " <<tokens[i].line_no << ": invalid character" << std::endl;
		}
	}
}
bool store_tokens_to_file(std::string file_name, const evl_tokens &tokens) {
	std::ofstream output_file(file_name.c_str());
	if(!output_file) {
		std::cerr << "I can't write" << output_file << "." << std::endl;
		return false;
	}
	display_tokens(output_file, tokens);
	return true;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "You should provide a file name." << std::endl;
        return -1;
    }

	std::string evl_file = argv[1];
	evl_tokens tokens;
	if(!extract_tokens_from_file(evl_file, tokens)) {
		return -1;
	}
	display_tokens(std::cout, tokens);
	if (!store_tokens_to_file(evl_file + ".tokens", tokens)) {
		return -1;
	}
	return 0;
}

