#include "Node.hpp"

namespace ravenscript
{
namespace ast
{

void Node::Print(std::ostream& ostream, int padding)
{

}

int Node::GetPriority() const 
{
	return 0;
}

NodePtr Node::GetSwappableL() const {
	return NodePtr();
}

NodePtr Node::GetSwappableR() const {
	return NodePtr();
}

void Node::InsertSwappableL(const NodePtr& node)
{
	
}

void Node::InsertSwappableR(const NodePtr& node)
{
	
}

NodePtr Node::Align()
{
	return GetSelfPtr();
}

std::shared_ptr<Node> Node::GetSelfPtr()
{
	return shared_from_this();
}

void Node::PrintPadding(std::ostream& ostream, int padding)
{
	for (int i = 0; i < padding; i++)
	{
		ostream << "  ";
	}
}

}
}
