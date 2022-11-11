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
	
	Postfix obj(input);
	std::cout << obj << std::endl;
}

