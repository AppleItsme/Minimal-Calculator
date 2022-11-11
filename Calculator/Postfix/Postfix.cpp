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

//A+B*C-(e*C-d)
//A    
//A     +
//A B    +
//A B C   *+
//A B C*+   -
//A B C*+   (-
//A B C*+ C   (-
//A B C*+ C   *(-
//A B C*+ C e   *(-
//A B C*+ C e*  -(-
//A B C*= C e*--


	void Postfix::pop(bool full) {
		for(int i = this->operator_stack.size()-1; i > -1; i--) {
			if(DEBUG_MODE) {
				std::cout << "{"; 
				for(const auto& v : this->operator_stack) {
					std::cout << " " << v;
				}
				std::cout << " }" << std::endl << "Current popped operator: " << this->operator_stack[i] << std::endl;
			}
			if(this->operator_stack[i] == ')' || this->operator_stack[i] == '(') {
				this->operator_stack.pop_back();
				if(full)
					continue;
				break;
			}
			this->number_stack.push_back(PostfixStackValue(false, this->operator_stack[i]));
			this->operator_stack.pop_back();
			if(DEBUG_MODE) {
				std::cout << "number_stack: {"; 
				for(const auto& v : this->number_stack) {
					if(v.number) {
						std::cout << " " << v.val;
						continue;
					}
					std::cout << " " << (char)v.val;
				}
				std::cout << " }" << std::endl;
			}
		}
	}

	Postfix::Postfix(std::string_view tokens) {
#define is_low_precedence(what) std::none_of(high_precedence.begin(), high_precedence.end(), [what](char v) { return v == what;})
		this->number_stack = {};
		this->operator_stack = {};
		const std::array<char, 3> high_precedence = {'*', '/', '%'};
		for(size_t i = 0; i < tokens.size(); i++) {
			char previous_operator = this->operator_stack.size() > 0 ? this->operator_stack[this->operator_stack.size()-1] : '\0';
			if(std::isdigit(tokens[i])) {
				std::string num = "";
				for(; i < tokens.size() && std::isdigit(tokens[i]); i++){
					num += tokens[i];
				}
				this->number_stack.push_back(PostfixStackValue(true, std::stol(num)));
				if(DEBUG_MODE) {
					std::cout << "==================" << std::endl 
						<< *this << std::endl << "------------------" << std::endl;
				}
			}
			if(DEBUG_MODE) {
				std::cout << "Previous Operator: " << previous_operator << std::endl 
				<< "Current Operator: " << tokens[i] << std::endl;
			}
			if(tokens[i] == '\0') {
				break;
			}
			
			char current_char = tokens[i];
			
			switch(current_char) {
				case ')': {
					this->pop(false);
					continue;
				}
				case '(': {
					if(tokens[i-1] == '-') {
						this->number_stack.push_back(PostfixStackValue(true, 0));
					}
					goto PUSH;
				}
				case '-': {
					if(tokens[i-1] == '(') {
						this->number_stack.push_back(PostfixStackValue(true, 0));
					}
				}
				default:
					if(previous_operator == '\0') {
						goto PUSH;
					} else if(is_low_precedence(current_char) && !is_low_precedence(previous_operator) && current_char != '(') {
						this->pop(false);
					}
			}

			PUSH:
			this->operator_stack.push_back(tokens[i]);
		}
		this->pop(true);
		std::cout << *this;
	}

	std::ostream& operator<<(std::ostream& os, const Postfix& postfix) {
		os << "Number stack: ";
		for(const auto& v : postfix.number_stack) {
			if(v.number) {
				os << "'" << v.val << "' ";
				continue;
			}
			os << "'" << (char)v.val << "' ";
		}
		os << std::endl << "Operand stack: ";
		for(const auto& v : postfix.operator_stack)
			os << "'" << v << "' ";
		os << std::endl;

		return os;
	}
};
