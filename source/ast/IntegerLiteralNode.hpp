#pragma once
#include "LiteralNode.hpp"

namespace ravenscript
{
namespace ast
{

class IntegerLiteralNode : public LiteralNode
{
public:
	explicit IntegerLiteralNode(int value) : m_value(value) {}
	virtual ~IntegerLiteralNode() = default;

	int GetIntegerValue() const { return m_value; }
	virtual std::string GetValue() override { return std::to_string(m_value); }

	virtual void Print(std::ostream& ostream, int padding) override
	{
		PrintPadding(ostream, padding);
		ostream << "<Integer>" << m_value << "</Integer>" << std::endl;
	}

private:
	int m_value;
};

}
}
