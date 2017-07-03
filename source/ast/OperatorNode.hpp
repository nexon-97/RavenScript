#pragma once
#include "Node.hpp"
#include "Operator.hpp"

namespace ravenscript
{
namespace ast
{

class OperatorNode : public Node
{
public:
	explicit OperatorNode(Operator op) : m_operator(op) {}
	virtual ~OperatorNode() = default;

	Operator GetOperator() const { return m_operator; }

	void SetRValue(const NodePtr& rvalue) { m_rvalue = rvalue; }
	NodePtr GetRValue() const { return m_rvalue; }

protected:
	Operator m_operator;
	NodePtr m_rvalue;
};

}
}
