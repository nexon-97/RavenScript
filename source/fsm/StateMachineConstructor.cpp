#include "StateMachineConstructor.hpp"
#include "TerminalState.hpp"
#include "DigitState.hpp"
#include "LetterState.hpp"
#include "WordState.hpp"

namespace ravenscript
{
namespace fsm
{

StateMachinePtr StateMachineConstructor::ConstructIdentifierFSM()
{
	StateMachinePtr identifierFsm = std::make_shared<StateMachine>();
	auto startState = identifierFsm->GetEntryState();
	auto finalState = identifierFsm->GetFinalState();
	startState->SetName("[START]");
	finalState->SetName("[FINAL]");

	auto letterState = std::make_shared<LetterState>();
	letterState->SetName("[LETTER]");
	auto digitState = std::make_shared<DigitState>();
	digitState->SetName("[DIGIT]");
	identifierFsm->AddState(letterState);
	identifierFsm->AddState(digitState);

	identifierFsm->AddTransition(startState, letterState, 0);
	identifierFsm->AddTransition(letterState, digitState, 0);
	identifierFsm->AddTransition(digitState, letterState, 0);
	identifierFsm->AddTransition(letterState, finalState, 0);
	identifierFsm->AddTransition(digitState, finalState, 0);
	identifierFsm->AddTransition(letterState, letterState, 0);
	identifierFsm->AddTransition(digitState, digitState, 0);

	return identifierFsm;
}

StateMachinePtr StateMachineConstructor::ConstructOperatorFSM()
{
	StateMachinePtr operatorFsm = std::make_shared<StateMachine>();
	auto startState = operatorFsm->GetEntryState();
	startState->SetName("[START]");
	auto finalState = operatorFsm->GetFinalState();
	finalState->SetName("[FINAL]");

	auto dotState = std::make_shared<WordState>(".");
	dotState->SetName("[.]");
	auto assignmentState = std::make_shared<WordState>("=");
	assignmentState->SetName("[=]");
	operatorFsm->AddState(dotState);
	operatorFsm->AddState(assignmentState);

	operatorFsm->AddTransition(startState, dotState, 0);
	operatorFsm->AddTransition(startState, assignmentState, 0);
	operatorFsm->AddTransition(dotState, finalState, 0);
	operatorFsm->AddTransition(assignmentState, finalState, 0);

	return operatorFsm;
}

StateMachinePtr StateMachineConstructor::ConstructExpressionFSM()
{
	StateMachinePtr expressionFsm = std::make_shared<StateMachine>();
	auto startState = expressionFsm->GetEntryState();
	auto finalState = expressionFsm->GetFinalState();

	auto identifierState = ConstructIdentifierFSM();
	identifierState->SetName("[ID 1]");
	auto braceOpenState = std::make_shared<TerminalState>(std::set<char> { '(' });
	braceOpenState->SetName("[(]");
	auto braceCloseState = std::make_shared<TerminalState>(std::set<char> { ')' });
	braceCloseState->SetName("[)]");
	auto operatorState = ConstructOperatorFSM();
	operatorState->SetName("[OP]");
	auto expressionNestedState1 = std::make_shared<StateMachine>(*expressionFsm);
	expressionNestedState1->SetName("[EXPR 1]");
	auto expressionNestedState2 = std::make_shared<StateMachine>(*expressionFsm);
	expressionNestedState2->SetName("[EXPR 2]");
	auto identifierState2 = std::make_shared<StateMachine>(*identifierState);
	identifierState2->SetName("[ID 2]");

	expressionFsm->AddState(identifierState);
	expressionFsm->AddState(braceOpenState);
	expressionFsm->AddState(braceCloseState);
	expressionFsm->AddState(operatorState);

	expressionFsm->AddTransition(startState, braceOpenState, 2);
	expressionFsm->AddTransition(braceOpenState, expressionNestedState1, 0);
	expressionFsm->AddTransition(expressionNestedState1, braceCloseState, 0);
	expressionFsm->AddTransition(braceCloseState, finalState, 0);

	expressionFsm->AddTransition(startState, identifierState2, 1);
	expressionFsm->AddTransition(identifierState2, operatorState, 0);
	expressionFsm->AddTransition(operatorState, expressionNestedState2, 0);
	expressionFsm->AddTransition(expressionNestedState2, finalState, 0);

	expressionFsm->AddTransition(startState, identifierState, 0);
	expressionFsm->AddTransition(identifierState, finalState, 0);

	return expressionFsm;
}

}
}
