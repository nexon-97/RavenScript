#pragma once

namespace ravenscript
{
namespace ast
{

class Node
{
public:
	Node() = default;
	virtual ~Node() = default;

	virtual void Print() {}
};

using NodePtr = std::shared_ptr<Node>;

}
}
