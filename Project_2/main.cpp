#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include "tokens.h"
#include "statements.h"

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
	
	//display_tokens(std::cout, tokens);
	if (!store_tokens_to_file(evl_file + ".tokens", tokens)) {
		return -1;
	}

	evl_statements statements;
	if(!group_tokens_into_statements(statements, tokens)){
		return -1;
	}

	//display_statements(std::cout,statements);	//displays before the sorting
	if (!store_statements_to_file(evl_file + ".statements", statements)) {
		return -1;
	}

	evl_statements::const_iterator mod_itr;
	if (!reorder_statements_list(mod_itr,statements)) {		//Reorders the statements list to put wires first
			return -1;
	}

	//display_statements(std::cout,statements);	//displays after the sort is performed
	evl_modules modules;
	for (evl_statements::iterator iter = statements.begin(); iter != statements.end(); ++iter) {
		if (!process_module_statements(modules,*iter)) {
			return -1;
		}
	}

	//display_module(std::cout,modules);
	if (!store_module_to_file(evl_file + ".syntax", modules)) {
		return -1;
	}

	std::cout << "Successfully wrote the following files: " << std::endl;
	std::cout << evl_file + ".tokens" << std::endl;
	std::cout << evl_file + ".statements" << std::endl;
	std::cout << evl_file + ".syntax" << std::endl;
	return 0;
}

