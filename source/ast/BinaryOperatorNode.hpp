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
	explicit BinaryOperatorNode(Operator op) 
		: OperatorNode(op) 
	{
		SetType(NodeType::BinaryOperator);
	}
	virtual ~BinaryOperatorNode() = default;

	void SetLValue(const NodePtr& lvalue) { m_lvalue = lvalue; }
	NodePtr GetLValue() const { return m_lvalue; }

	virtual int GetPriority() const override;
	virtual NodePtr GetSwappableL() const override;
	virtual NodePtr GetSwappableR() const override;
	virtual void InsertSwappableL(const NodePtr& node) override;
	virtual void InsertSwappableR(const NodePtr& node) override;
	virtual NodePtr Align() override;

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
