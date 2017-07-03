#include "FunctionCallState.hpp"
#include <algorithm>
#include <iterator>
#include "ast/FunctionCallNode.hpp"

namespace ravenscript
{
namespace fsm
{

FunctionCallState::FunctionCallState()
	: StateMachine()
{
}

StatePtr FunctionCallState::Clone()
{
	return StatePtr(new FunctionCallState(*this));
}

ast::NodePtr FunctionCallState::Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	// Reset fsm state to entry
	SetCurrentState(m_entryState);

	// Push identifier parts container for recursion
	ParsingPhase phase = ParsingPhase::FunctionId;
	FunctionCallData callData;

	m_parsingPhase = &phase;
	m_callData = &callData;

	// Enter recursion
	auto output = DoStep(istream, end, inputNode);

	if (!!output)
	{
		auto functionCallNode = std::make_shared<ast::FunctionCallNode>(callData.name);
		functionCallNode->SetParams(callData.params);

		return functionCallNode;
	}

	return ast::NodePtr();
}

ast::NodePtr FunctionCallState::DoStep(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	auto restoreState = m_currentState;

	std::vector<StatePtr> validStates;
	ConstructValidStates(validStates, istream, end);

	ast::NodePtr parseResult;
	for (const StatePtr& state : validStates)
	{
		LexicalToken* streamOffset = istream;
		ParsingPhase* phase = m_parsingPhase;
		FunctionCallData* callData = m_callData;
		SetCurrentState(state);

		switch (state->GetId())
		{
			case StateId::Comma:
				*m_parsingPhase = ParsingPhase::Comma;
				break;
			case StateId::Expression:
				*m_parsingPhase = ParsingPhase::Expression;
				break;
			case StateId::BraceOpen:
				*m_parsingPhase = ParsingPhase::BraceOpen;
				break;
			case StateId::BraceClose:
				*m_parsingPhase = ParsingPhase::BraceClose;
				break;
		}

		parseResult = state->Parse(istream, end, inputNode);

		SetCurrentState(state);
		m_parsingPhase = phase;
		m_callData = callData;

		if (!!parseResult)
		{
			switch (*m_parsingPhase)
			{
				case ParsingPhase::FunctionId:
					m_callData->name = parseResult;
					break;
				case ParsingPhase::Expression:
					m_callData->params.push_back(parseResult);
					break;
			}

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
