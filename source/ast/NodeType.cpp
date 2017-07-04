#include "NodeType.hpp"
#include "BinaryOperatorNode.hpp"

namespace ravenscript
{
namespace ast
{

int GetNodePriority(const NodePtr& node)
{
	auto nodeType = node->GetType();

	switch (nodeType)
	{
	case NodeType::Identifier:
		return 101;
	case NodeType::Literal:
		return 102;
	case NodeType::FunctionCall:
		return 95;
	case NodeType::BinaryOperator:
	{
		auto binaryOpNode = std::dynamic_pointer_cast<BinaryOperatorNode>(node);
		if (!!binaryOpNode)
		{
			return utils::GetOperatorPriority(binaryOpNode->GetOperator());
		}
	}
	}

	return 0;
}

}
}
