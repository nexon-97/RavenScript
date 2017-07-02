#include "StateMachineConstructor.hpp"
#include "TerminalState.hpp"
#include "DigitState.hpp"
#include "LetterState.hpp"
#include "WordState.hpp"
#include "IdentifierStateMachine.hpp"
#include "RecursiveState.hpp"

namespace ravenscript
{
namespace fsm
{

StateMachinePtr StateMachineConstructor::ConstructIdentifierFSM()
{
	StateMachinePtr identifierFsm = std::make_shared<IdenitifierStateMachine>();
	identifierFsm->SetName("[ID]");
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

	return identifierFsm;
}

StateMachinePtr StateMachineConstructor::ConstructOperatorFSM()
{
	StateMachinePtr operatorFsm = std::make_shared<StateMachine>();
	operatorFsm->SetName("[OPERATOR]");
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
	expressionFsm->SetName("[EXPRESSION]");
	auto startState = expressionFsm->GetEntryState();
	auto finalState = expressionFsm->GetFinalState();

	auto identifierState = ConstructIdentifierFSM();
	identifierState->SetName("[ID 1]");
	auto numberState = std::make_shared<DigitState>();
	numberState->SetName("[NUMBER]");
	auto braceOpenState = std::make_shared<TerminalState>(std::set<char> { '(' });
	braceOpenState->SetName("[(]");
	auto braceCloseState = std::make_shared<TerminalState>(std::set<char> { ')' });
	braceCloseState->SetName("[)]");
	auto operatorState = ConstructOperatorFSM();
	operatorState->SetName("[OP]");
	auto expressionNestedState1 = std::make_shared<RecursiveState>(expressionFsm.get());
	expressionNestedState1->SetName("[EXPR 1]");
	auto expressionNestedState2 = std::make_shared<RecursiveState>(expressionFsm.get());
	expressionNestedState2->SetName("[EXPR 2]");
	auto expressionNestedState3 = std::make_shared<RecursiveState>(expressionFsm.get());
	expressionNestedState3->SetName("[EXPR 3]");
	auto identifierState2 = identifierState->Clone();
	identifierState2->SetName("[ID 2]");
	auto identifierState3 = identifierState->Clone();
	identifierState3->SetName("[ID 3]");
	auto braceOpenState2 = braceOpenState->Clone();
	braceOpenState2->SetName("[(]");
	auto braceCloseState2 = braceCloseState->Clone();
	braceCloseState2->SetName("[)]");
	auto commaState = std::make_shared<TerminalState>(std::set<char> { ',' });
	commaState->SetName("[,]");

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

	expressionFsm->AddTransition(startState, numberState, 0);
	expressionFsm->AddTransition(numberState, finalState, 0);

	expressionFsm->AddTransition(startState, identifierState3, 2);
	expressionFsm->AddTransition(identifierState3, braceOpenState2, 0);
	expressionFsm->AddTransition(braceOpenState2, expressionNestedState3, 0);
	expressionFsm->AddTransition(expressionNestedState3, commaState, 0);
	expressionFsm->AddTransition(commaState, expressionNestedState3, 0);
	expressionFsm->AddTransition(expressionNestedState3, braceCloseState2, 0);
	expressionFsm->AddTransition(braceOpenState2, braceCloseState2, 0);
	expressionFsm->AddTransition(braceCloseState2, finalState, 0);

	return expressionFsm;
}

}
}
