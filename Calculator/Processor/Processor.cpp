#include "Processor.hpp"
#include <algorithm>
#include <cstddef>
#include <array>
#include "../AST/AST.hpp"

namespace Calculator {
	Entity MergePairEntities(const size_t first, const size_t second, std::vector<Entity>& AST) {
		int num = 0;
		Entity second_obj = AST[second];
		if(second+1 < AST.size()) {
			switch(AST[second].suffix) {
				case '*':
				case '/':
				case '%':
					second_obj = MergePairEntities(second, second + 1, AST);
					break;
				default:
					break;
			}
		}

		switch(AST[first].suffix) {
			case '-':
				num = AST[first].number - second_obj.number;
				break;
			case '+':
				num = AST[first].number + second_obj.number; 
				break;
			case '/':
				num = AST[first].number / second_obj.number ;
				break;
			case '*':
				num = AST[first].number * second_obj.number;
				break;
			case '%':
				num = AST[first].number % second_obj.number;
				break;
		}
		AST.erase(AST.begin() + second);
		return Entity(num, second_obj.suffix);
	}
	
	void Calculate(std::vector<Entity>& AST) {
		while(AST.size() > 1) {
			if(DEBUG_MODE) {
				DebugAST(AST, "=====Beginning=====", "=================="); 
			}
			//AST.insert(AST.begin() + max_depth_i, result);
			//AST.erase(AST.begin() + max_depth_i+1);
			AST[0] = MergePairEntities(0, 1, AST);
			if(DEBUG_MODE) {
				std::cout << "=====End=====" << std::endl;
				for(const auto& v: AST) 
					std::cout << "AST: " << v << std::endl;
				std::cout << "=============" << std::endl;
			}
		}
	}
}
