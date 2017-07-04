#pragma once
#include "NodeType.hpp"
#include "SwapBehaviour.hpp"
#include <ostream>
#include <memory>

namespace ravenscript
{
namespace ast
{

class Node 
	: public SwapBehaviour
	, public std::enable_shared_from_this<Node>
{
public:
	Node() {}
	virtual ~Node() = default;

	virtual void Print(std::ostream& ostream, int padding);

	void SetType(NodeType type) { m_type = type; }
	NodeType GetType() const { return m_type; }

	virtual int GetPriority() const override;
	virtual NodePtr GetSwappableL() const override;
	virtual NodePtr GetSwappableR() const override;
	virtual void InsertSwappableL(const NodePtr& node) override;
	virtual void InsertSwappableR(const NodePtr& node) override;
	virtual NodePtr Align() override;

	std::shared_ptr<Node> GetSelfPtr();

protected:
	void PrintPadding(std::ostream& ostream, int padding);

protected:
	NodeType m_type = NodeType::None;
};

using NodePtr = std::shared_ptr<Node>;

}
}
