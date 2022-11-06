#include "App.hpp"

#include <cctype>
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

std::vector<char> lexer(std::string str) {
	size_t pos = str.find("-(-");
	while(pos != std::string::npos) {
		str.replace(str.begin()+pos, str.begin()+pos+3, "+(");
		pos = str.find("-(-");
	}	

	std::vector<char> vec;
	if(str.find("/0") != std::string::npos) {
		std::cout << "no division by zero!" << std::endl;
		return vec;
	}
	const std::array<char, 7> allowed_nondigit_char = {'%', '+', '-', '/', '(', ')', '*'};
	for(const char& i : str) {
		if(!std::none_of(allowed_nondigit_char.begin(), allowed_nondigit_char.end(), [&i](char v) { return i == v; }) 
			|| std::isdigit(i)) {
			vec.push_back(i);
			continue;
		}
		std::cout << "Syntax error: '" << i << "'; Invalid character bozo" << std::endl;
		vec.clear();
		break;
	}
	return vec;
}

void Calculator::Initialize() {
	std::cout << "Type in the equation below (No whitespaces allowed ;_;)" << std::endl;
	
	std::string input;
	std::cin >> input;
	
	auto lexed_chars = lexer(input);
	if(lexed_chars.empty())
		return;
	std::vector<Entity> result = Calculator::ParseToAST(lexed_chars);
	Calculator::Calculate(result);
	std::cout << HIGHLIGHT_COLOR << "Result: " << HIGHLIGHT_COLOR_2 << result[0].number << ERASESTYLE << std::endl;
}

