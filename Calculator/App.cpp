#include "App.hpp"

#include <cctype>
#include <cstddef>
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include "AST/AST.hpp"
#include "Processor/Processor.hpp"
#include "GlobalTypes.hpp"

/*
 *	Intentions:
 *	Works with basic operators such as *, +, /, - and % (out of programmer urges)
 *	5 + 5 * 7 = 40 and not 70
 *	(5 + 5) * 7 = 70
 */

std::vector<char> Lexer(std::string str) {
	std::vector<char> vec;
	const std::array<char, 7> allowed_nondigit_char = {'%', '+', '-', '/', '*'};
	for(const char& i : str) {
		if(!std::none_of(allowed_nondigit_char.begin(), allowed_nondigit_char.end(), [&i](char v) { return i == v; }) 
			|| std::isdigit(i)) {
			vec.push_back(i);
			continue;
		}
		std::cout << "Syntax error: '" << i << "'; Invalid character bozo" << std::endl;
		std::cout << str << std::endl;
		vec.clear();
		break;
	}
	return vec;
}

std::string isolateDeepest(std::string& str, std::vector<std::string>& depth_tree) {
	size_t pos1 = str.find('(');
	size_t pos2 = str.find_last_of(')');
	if(pos2 != std::string::npos || pos1 != std::string::npos) {
		str.erase(0, pos1+1);
		str.erase(pos2-pos1-1);
		depth_tree.push_back(str);
		str = isolateDeepest(str, depth_tree);
	}
	return str;
}

size_t Process(std::string str, size_t& err) {	
	size_t result = 0;
	std::vector<std::string> depth_tree = {str};
	isolateDeepest(str, depth_tree);

	for(int i = depth_tree.size()-1; i >= 0; i--) {
		auto lexed = Lexer(depth_tree[i]);
		if(lexed.empty()) {
			err = 1;	
			return result;
		}
		auto cur_result = Calculator::ParseToAST(lexed);
		Calculator::Calculate(cur_result);
		if(i > 0) {
			std::string num_str = std::to_string(cur_result[0].number);
			size_t pos = depth_tree[i-1].find(depth_tree[i])-1;

			depth_tree[i-1].replace(depth_tree[i-1].begin() + pos,
					depth_tree[i-1].begin() + pos + depth_tree[i].size()+2,
					num_str);
		}
		result = cur_result[0].number;
	}
	return result;
}



void Calculator::Initialize() {
	std::cout << "Type in the equation below (No whitespaces allowed ;_;)" << std::endl;
	
	std::string input;
	std::cin >> input;
	size_t err = 0;
	std::cout << HIGHLIGHT_COLOR << "Result: " << HIGHLIGHT_COLOR_2 
		<< Process(input, err) << ERASESTYLE << std::endl 
		<< err << std::endl;
}

