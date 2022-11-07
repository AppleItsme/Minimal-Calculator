#pragma once
#include <vector>
#include <iostream>
#include "../GlobalTypes.hpp"
/*	1+10%2-5(10-1)
 *	1+ (10%2) -5* (10-1)			
 *1+ (10% 2) -5* (10- 1)
 *
 *
 */

namespace Calculator {
//expression
/*
 * Suffix operator
 * Prefix operator
 * scope
 */
struct Entity {
	char prefix;
	char suffix;
	int number;

	Entity(char prefix, int number, char suffix);
	friend std::ostream& operator<<(std::ostream &os, const Entity expression);
};

std::vector<Entity> ParseToAST(const std::vector<char>&);

inline void DebugAST(std::vector<Entity>& arr, const std::string start, const std::string end) {
	std::cout << HIGHLIGHT_COLOR << start << ERASESTYLE << std::endl;
	for(const Entity& v : arr)
		std::cout << v << std::endl;
	std::cout << HIGHLIGHT_COLOR << end << ERASESTYLE << std::endl;
}

}
