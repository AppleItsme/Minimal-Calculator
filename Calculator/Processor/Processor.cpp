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
					if(AST[second+1].depth == AST[second].depth)
						second_obj = MergePairEntities(second, second + 1, AST);
					break;
				default:
					break;
			}
		}

		switch(AST[first].suffix) {
			case '-':
				num = AST[first].number + 
					((second_obj.number > 0 || second_obj.depth > AST[first].depth) &&
					second_obj.prefix == '-' ? -1 : 1) * second_obj.number;
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
		return Entity(AST[first].prefix, num, second_obj.suffix, AST[first].depth);
	}
	
	void Calculate(std::vector<Entity>& AST) {
		if(DEBUG_MODE) {
			DebugAST(AST, "=====Beginning=====", "=================="); 
		}
		size_t max_depth_i = 0;
		int max_depth = 0;
		for(size_t i = 0; i < AST.size(); i++) {
			if(AST[i].depth > max_depth) {
				max_depth_i = i;
				max_depth = AST[i].depth;
			}
		}
		Entity result = AST[max_depth_i];
		if(max_depth_i+1 < AST.size() && AST[max_depth_i+1].depth == max_depth)
			result = MergePairEntities(max_depth_i, max_depth_i+1, AST);
		result.depth -= result.depth > 0;
		AST.insert(AST.begin() + max_depth_i, result);
		AST.erase(AST.begin() + max_depth_i+1);
		if(DEBUG_MODE) {
			std::cout << "=====End=====" << std::endl;
			for(const auto& v: AST) 
				std::cout << "AST: " << v << std::endl;
			std::cout << "=============" << std::endl;
		}
		if(AST.size() > 1)
			Calculate(AST);
	}
}
