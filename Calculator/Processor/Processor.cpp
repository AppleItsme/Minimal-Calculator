#include "Processor.hpp"
#include <iostream>

inline void PerformOperation(long& result_num, const long& num1, char oper) {
	switch(oper) {
		case '-':
			result_num -= num1;
			break;
		case '+':
			result_num += num1;
			break;
		case '*':
			result_num *= num1;
			break;
		case '/':
			result_num /= num1;
			break;
		case '%':
			result_num %= num1;
			break;
	}
	if(DEBUG_MODE) {
		std::cout << "PerformOperation::result_num: " << result_num << std::endl;
	}
}

long Calculator::Calculate(Postfix& obj) {
	if(DEBUG_MODE)
		std::cout << std::endl;
	for(int i = 0; i < obj.number_stack.size() && obj.number_stack.size() >= 3; i++) {
		if(!obj.number_stack[i].number) {
			PerformOperation(obj.number_stack[i-2].val, obj.number_stack[i-1].val, obj.number_stack[i].val);
			obj.number_stack.erase(obj.number_stack.begin()+i-1, obj.number_stack.begin()+i+1);
			i -= 2;
			if(DEBUG_MODE)
				std::cout << obj;
		}
	}
	return obj.number_stack[0].val;
}
