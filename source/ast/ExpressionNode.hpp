#pragma once
#include "LiteralNode.hpp"

namespace ravenscript
{
namespace ast
{

class StringLiteralNode : public LiteralNode
{
public:
	explicit StringLiteralNode(char* value) : m_value(value) {}
	virtual ~StringLiteralNode() = default;

	virtual std::string GetValue() override { return m_value; }

private:
	std::string m_value;
};

}
}
