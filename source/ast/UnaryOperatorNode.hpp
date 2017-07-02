#pragma once
#include "OperatorNode.hpp"

namespace ravenscript
{
namespace ast
{

class UnaryOperatorNode : public OperatorNode
{
public:
	explicit UnaryOperatorNode(Operator op) : OperatorNode(op) {}
	virtual ~UnaryOperatorNode() = default;

	NodePtr GetRValue() const { return m_rvalue; }

private:
	NodePtr m_rvalue;
};

}
}
