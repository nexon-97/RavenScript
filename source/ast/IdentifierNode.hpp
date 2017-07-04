#pragma once
#include "Node.hpp"

namespace ravenscript
{
namespace ast
{

class IdentifierNode : public Node
{
public:
	explicit IdentifierNode(const std::string& value)
		: m_value(value) 
	{
		SetType(NodeType::Identifier);
	}
	virtual ~IdentifierNode() = default;

	const std::string& GetValue() const { return m_value; }

	virtual void Print(std::ostream& ostream, int padding) override
	{
		PrintPadding(ostream, padding);
		ostream << "<Identifier>" << m_value << "</Identifier>" << std::endl;
	}

private:
	std::string m_value;
};

}
}
