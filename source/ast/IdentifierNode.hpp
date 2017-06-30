#pragma once
#include "Node.hpp"

namespace ravenscript
{
namespace ast
{

class IdentifierNode : public Node
{
public:
	explicit IdentifierNode(const std::string& value) : m_value(value) {}
	virtual ~IdentifierNode() = default;

	const std::string& GetValue() const { return m_value; }

private:
	std::string m_value;
};

}
}
