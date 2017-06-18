#pragma once
#include "LexicalToken.hpp"

#include <vector>

namespace ravenscript
{

class LexicalTokenizer
{
public:
	bool Parse(char* textBlob, std::vector<LexicalToken>* tokensList);
};

}
