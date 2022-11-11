#include "Postfix.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

namespace Calculator {
	PostfixStackValue::PostfixStackValue(bool number, long val) {
		this->number = number;
		this->val = val;
	}

//A+B*C-(d+e)
//A    
//A     +
//A B    +
//A B C   *+
//A B C*+   -
//A B C*+   (-
//A B C*+ d   (-
//A B C*+ d   +(-
//A B C*+ d e   +(-
//A B C*+ d e+-


/*
 * A BC+ d e+-
 * (A+BC) d e+-
 * (A+BC) (d+e)-
 * (A+BC)-(d+e)
 */
	void Postfix::pop(char until) {
		for(int i = this->operator_stack.size()-1; i > -1; i--) {
			if(this->operator_stack[i] != until) {
				this->number_stack.push_back(PostfixStackValue(false, this->operator_stack[i]));
				this->operator_stack.pop_back();
			}
			return;
		}
	}

	Postfix::Postfix(std::string_view tokens) {
#define is_low_precedence(what) std::none_of(high_precedence.begin(), high_precedence.end(), [what](char v) { return v == what;})
		const std::array<char, 3> high_precedence = {'*', '/', '%'};
		for(int i = 0; i < tokens.size(); i++) {
			char cur_char = tokens[i];
			if(std::isdigit(cur_char)) {
				std::string num = "";
				for(; i < tokens.size() && std::isdigit(tokens[i]); i++){
					num += tokens[i];
				}
				this->number_stack.push_back(PostfixStackValue(true, std::stol(num)));
				continue;
			}
			char previous_operator = this->operator_stack[this->operator_stack.size()-1];
			//- -> *+
			if(cur_char == ')') {
				this->pop('(');
				continue;
			} else if(!is_low_precedence(cur_char) && is_low_precedence(previous_operator) && cur_char != '(') {
				this->pop('\0');
			}
			this->operator_stack.push_back(cur_char);
		}
		this->pop('\0');
	}

	std::ostream& operator<<(std::ostream& os, const Postfix& postfix) {
		os << "Number stack: ";
		for(const auto& v : postfix.number_stack) {
			if(v.number) {
				os << v.val << " ";
				continue;
			}
			os << (char)v.val;
		}
		os << std::endl << "Operand stack: ";
		for(const auto& v : postfix.operator_stack)
			os << v;
		os << std::endl;

		return os;
	}
};
