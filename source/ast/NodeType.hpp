#pragma once
#include <memory>

namespace ravenscript
{
namespace ast
{

enum class NodeType
{
	None,
	BinaryOperator,
	UnaryOperator,
	FunctionCall,
	Identifier,
	Literal,
};

using NodePtr = std::shared_ptr<class Node>;
int GetNodePriority(const NodePtr& node);

}
}
