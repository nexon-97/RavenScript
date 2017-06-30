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

private:
	int m_value;
};

}
}
