#include "OperatorState.hpp"
#include "Utils.hpp"
#include "ast/BinaryOperatorNode.hpp"

namespace ravenscript
{
namespace fsm
{

ast::NodePtr OperatorState::Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	auto outputNode = std::make_shared<ast::BinaryOperatorNode>(m_operator);
	outputNode->SetLValue(inputNode);

	istream++;

	return outputNode;
}

bool OperatorState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	char* value = istream->GetValue();
	int length = strlen(value);

	if (length == 1)
	{
		Operator op = utils::CharToOperator(*value);
		return op == m_operator;
	}

	return false;
}

StatePtr OperatorState::Clone()
{
	return StatePtr(new OperatorState(*this));
}

}
}
