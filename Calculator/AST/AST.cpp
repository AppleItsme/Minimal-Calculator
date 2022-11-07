#include "AST.hpp"
#include <cstddef>
#include <ostream>
#include <vector>
#include <cctype>
#include <string>

namespace Calculator {
	Entity::Entity(char prefix, int number, char suffix) {
		this->prefix = prefix;
		this->suffix = suffix;
		this->number = number;
	}

	std::ostream& operator<<(std::ostream& os, const Entity expression) {
		os << "prefix: " << expression.prefix << std::endl
			<< "number: " << expression.number << std::endl
			<< "suffix: " << expression.suffix << std::endl;
		return os;
	}
	
	std::vector<Entity> ParseToAST(const std::vector<char>& chars) {
		std::vector<Entity> AST;
		size_t start_pos = 0;
		for(size_t i = 0; i < chars.size(); i++) {
			for(; i+1 < chars.size() && !std::isdigit(chars[i]); i++) {}
			start_pos = i;
			for(; i+1 < chars.size() && std::isdigit(chars[i+1]); i++) {}
			if(!std::isdigit(chars[i])) {
				break;				
			}
			std::string num = start_pos < i && i < chars.size()
				? std::string(chars.begin() + start_pos, chars.begin() + i + 1)
				: std::string(1, chars[i]);
			char prefix = (long long)start_pos-1 == -1 ? '\0' : chars[start_pos-1];
			if(prefix == '(' && (long long)start_pos-2 >= 0)
				prefix = chars[start_pos-2];
			char suffix = i+1 < chars.size() ? chars[i+1] : '\0';
			if(suffix == ')' && i+2 < chars.size())
				suffix = chars[i+2];

			AST.push_back(Entity(prefix, std::stoi(num), suffix));
		}
		if(DEBUG_MODE) {
			DebugAST(AST, "AST PARSING::", "::AST PARSING");
		}
		return AST;
	}

};
