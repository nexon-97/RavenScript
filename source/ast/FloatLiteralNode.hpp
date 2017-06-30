#pragma once
#include "LiteralNode.hpp"

namespace ravenscript
{
namespace ast
{

class FloatLiteralNode : public LiteralNode
{
public:
	explicit FloatLiteralNode(float value) : m_value(value) {}
	virtual ~FloatLiteralNode() = default;

	float GetFloatValue() const { return m_value; }
	virtual std::string GetValue() override { return std::to_string(m_value); }

private:
	float m_value;
};

}
}
