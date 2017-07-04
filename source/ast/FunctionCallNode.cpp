#include "FunctionCallNode.hpp"
#include "NodeType.hpp"

namespace ravenscript
{
namespace ast
{

int FunctionCallNode::GetPriority() const
{
	return 95;
}

NodePtr FunctionCallNode::GetSwappableL() const
{
	return NodePtr();
}

NodePtr FunctionCallNode::GetSwappableR() const
{
	return GetId();
}

void FunctionCallNode::InsertSwappableL(const NodePtr& node)
{
	SetId(node);
}

void FunctionCallNode::InsertSwappableR(const NodePtr& node)
{
	
}

NodePtr FunctionCallNode::Align()
{
	// Align children
	GetId()->Align();

	for (auto paramNode : m_paramNodes)
	{
		paramNode->Align();
	}

	return GetSelfPtr();
}

}
}
