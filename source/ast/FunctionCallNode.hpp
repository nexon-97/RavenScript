#pragma once
#include "OperatorNode.hpp"
#include "Utils.hpp"

namespace ravenscript
{
namespace ast
{

class FunctionCallNode : public Node
{
public:
	explicit FunctionCallNode(const NodePtr& idNode) : m_idNode(idNode) {}
	virtual ~FunctionCallNode() = default;

	void SetId(const NodePtr& idNode) { m_idNode = idNode; }
	NodePtr GetId() const { return m_idNode; }
	void SetParams(const std::vector<NodePtr> paramNodes) { m_paramNodes = paramNodes; }
	const std::vector<NodePtr>& GetParams() const { return m_paramNodes; }

	virtual void Print(std::ostream& ostream, int padding) override
	{
		PrintPadding(ostream, padding);
		ostream << "<FunctionCall>" << std::endl;

		PrintPadding(ostream, padding + 1);
		ostream << "<FunctionId>" << std::endl;
		m_idNode->Print(ostream, padding + 2);
		PrintPadding(ostream, padding + 1);
		ostream << "</FunctionId>" << std::endl;

		PrintPadding(ostream, padding + 1);
		ostream << "<Params>" << std::endl;

		for (const auto& paramNode : m_paramNodes)
		{
			paramNode->Print(ostream, padding + 2);
		}

		PrintPadding(ostream, padding + 1);
		ostream << "</Params>" << std::endl;

		PrintPadding(ostream, padding);
		ostream << "</FunctionCall>" << std::endl;
	}

private:
	NodePtr m_idNode;
	std::vector<NodePtr> m_paramNodes;
};

}
}
