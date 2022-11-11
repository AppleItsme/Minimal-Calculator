#include <cctype>
#include <cstddef>
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include "Postfix/Postfix.hpp"
#include "App.hpp"
#include "Processor/Processor.hpp"
#include "GlobalTypes.hpp"

void Calculator::Initialize() {
	std::cout << "Type in the equation below (No whitespaces allowed ;_;)" << std::endl;
	
	std::string input;
	std::cin >> input;
	Calculator::Postfix obj(input);
	long result = Calculator::Calculate(obj);

	std::cout << HIGHLIGHT_COLOR << "Result: " << HIGHLIGHT_COLOR_2 << result << ERASESTYLE << std::endl;
}

