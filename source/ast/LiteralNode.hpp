#pragma once
#include "Node.hpp"
#include <string>

namespace ravenscript
{
namespace ast
{

class LiteralNode : public Node
{
public:
	LiteralNode() = default;
	virtual ~LiteralNode() = default;

	virtual std::string GetValue() = 0;
};

using LiteralNodePtr = std::shared_ptr<LiteralNode>;

}
}
