#pragma once

namespace ravenscript
{
namespace ast
{

class Node;
class SwapBehaviour
{
public:
	virtual int GetPriority() const = 0;
	virtual NodePtr GetSwappableL() const = 0;
	virtual NodePtr GetSwappableR() const = 0;
	virtual void InsertSwappableL(const NodePtr& node) = 0;
	virtual void InsertSwappableR(const NodePtr& node) = 0;
	virtual NodePtr Align() = 0;
};

}
}
