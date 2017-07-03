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

	virtual void Print(std::ostream& ostream, int padding) {}

protected:
	void PrintPadding(std::ostream& ostream, int padding)
	{
		for (int i = 0; i < padding; i++)
		{
			ostream << "  ";
		}
	}
};

using NodePtr = std::shared_ptr<Node>;

}
}
