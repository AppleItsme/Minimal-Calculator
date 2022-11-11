#pragma once
#include <array>
#include <cstddef>
#include <ostream>
#include <vector>
#include <string_view>
#include "../GlobalTypes.hpp"

namespace Calculator {
	struct PostfixStackValue {
		bool number;
		long val;
		PostfixStackValue(bool, long);
	};
	struct Postfix {
		private:
			std::vector<char> operator_stack;
			void pop(char until);
			//number_stack[0][0] -> value; ..[0][1] -> operator or number 
		std::vector<PostfixStackValue> number_stack;
		Postfix(std::string_view tokens);
		friend std::ostream& operator<<(std::ostream& os, const Postfix& postfix);
	};
}
