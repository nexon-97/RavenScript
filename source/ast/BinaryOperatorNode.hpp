#pragma once
#include "OperatorNode.hpp"

namespace ravenscript
{
namespace ast
{

class BinaryOperatorNode : public OperatorNode
{
public:
	explicit BinaryOperatorNode(Operator op) : OperatorNode(op) {}
	virtual ~BinaryOperatorNode() = default;

	void SetLValue(const NodePtr& lvalue) { m_lvalue = lvalue; }
	NodePtr GetLValue() const { return m_lvalue; }

private:
	NodePtr m_lvalue;
};

}
}
