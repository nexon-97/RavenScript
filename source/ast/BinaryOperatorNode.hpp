#pragma once
#include "OperatorNode.hpp"
#include "Utils.hpp"

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

	virtual void Print(std::ostream& ostream, int padding) override
	{
		PrintPadding(ostream, padding);
		ostream << "<BinaryOperator '" << utils::OperatorToChar(GetOperator()) << "'>" << std::endl;
		
		if (m_lvalue) 
		{
			PrintPadding(ostream, padding + 1); ostream << "<LValue>" << std::endl;
			m_lvalue->Print(ostream, padding + 2);
			PrintPadding(ostream, padding + 1); ostream << "</LValue>" << std::endl;
		}
		if (m_rvalue)
		{
			PrintPadding(ostream, padding + 1); ostream << "<RValue>" << std::endl;
			m_rvalue->Print(ostream, padding + 2);
			PrintPadding(ostream, padding + 1); ostream << "</RValue>" << std::endl;
		}

		PrintPadding(ostream, padding);
		ostream << "</BinaryOperator>" << std::endl;
	}

private:
	NodePtr m_lvalue;
};

}
}
