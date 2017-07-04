#include "BinaryOperatorNode.hpp"

namespace ravenscript
{
namespace ast
{

int BinaryOperatorNode::GetPriority() const
{
	return utils::GetOperatorPriority(GetOperator());
}

NodePtr BinaryOperatorNode::GetSwappableL() const
{
	return GetRValue();
}

NodePtr BinaryOperatorNode::GetSwappableR() const
{
	return GetLValue();
}

void BinaryOperatorNode::InsertSwappableL(const NodePtr& node)
{
	SetLValue(node);
}

void BinaryOperatorNode::InsertSwappableR(const NodePtr& node)
{
	SetRValue(node);
}

NodePtr BinaryOperatorNode::Align()
{
	// Align children
	SetLValue(GetLValue()->Align());
	SetRValue(GetRValue()->Align());

	NodePtr result = GetSelfPtr();
	if (GetRValue()->GetPriority() < GetPriority())
	{
		auto rvalue = GetRValue();
		auto rSwappable = GetRValue()->GetSwappableR();
		if (!!rSwappable)
		{
			SetRValue(rSwappable);
			rvalue->InsertSwappableL(GetSelfPtr());

			result = rvalue;
		}
	}

	return result;
}

}
}
