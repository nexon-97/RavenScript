#include "IdentifierStateMachine.hpp"
#include <algorithm>
#include <iterator>
#include "ast/IdentifierNode.hpp"

namespace ravenscript
{
namespace fsm
{

IdenitifierStateMachine::IdenitifierStateMachine()
	: StateMachine()
{

}

StatePtr IdenitifierStateMachine::Clone()
{
	return StatePtr(new IdenitifierStateMachine(*this));
}

ast::NodePtr IdenitifierStateMachine::Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	// Reset fsm state to entry
	SetCurrentState(m_entryState);

	// Push identifier parts container for recursion
	std::vector<ast::LiteralNodePtr> identifiersParts;
	m_identifierParts = &identifiersParts;

	// Enter recursion
	auto output = DoStep(istream, end, inputNode);

	if (!!output)
	{
		// Construct identifier value
		std::string idenitiferValue;
		for (const auto& part : identifiersParts)
		{
			idenitiferValue += part->GetValue();
		}

		auto identifierNode = std::make_shared<ast::IdentifierNode>(idenitiferValue);
		return identifierNode;
	}

	return ast::NodePtr();
}

ast::NodePtr IdenitifierStateMachine::DoStep(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	auto restoreState = m_currentState;

	std::vector<StatePtr> validStates;
	ConstructValidStates(validStates, istream, end);

	ast::NodePtr parseResult;
	for (const StatePtr& state : validStates)
	{
		LexicalToken* streamOffset = istream;
		SetCurrentState(state);

		parseResult = state->Parse(istream, end, inputNode);
		auto literalNode = std::dynamic_pointer_cast<ast::LiteralNode>(parseResult);
		if (!!literalNode)
		{
			m_identifierParts->push_back(literalNode);
			return DoStep(istream, end, parseResult);
		}
		else
		{
			istream = streamOffset;
		}
	}

	if (!parseResult)
	{
		bool canTransitToFinalState = std::find(m_possibleStates.begin(), m_possibleStates.end(), m_finalState) != m_possibleStates.end();
		if (canTransitToFinalState)
		{
			parseResult = inputNode;
		}
	}

	SetCurrentState(restoreState);
	return parseResult;
}

}
}
