#include "StateMachineConstructor.hpp"
#include "TerminalState.hpp"
#include "DigitState.hpp"
#include "LetterState.hpp"
#include "WordState.hpp"
#include "IdentifierStateMachine.hpp"
#include "RecursiveState.hpp"
#include "OperatorState.hpp"
#include "FunctionCallState.hpp"

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

	auto dotState = std::make_shared<OperatorState>(Operator::Index);
	dotState->SetName("[.]");
	auto assignmentState = std::make_shared<OperatorState>(Operator::Assignment);
	assignmentState->SetName("[=]");

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
	expressionFsm->SetId(StateId::Expression);
	auto startState = expressionFsm->GetEntryState();
	auto finalState = expressionFsm->GetFinalState();

	auto identifierState = ConstructIdentifierFSM();
	identifierState->SetName("[ID 1]");
	auto numberState = std::make_shared<DigitState>();
	numberState->SetName("[NUMBER]");
	auto braceOpenState = std::make_shared<TerminalState>(std::set<char> { '(' });
	braceOpenState->SetName("[(]");
	braceOpenState->SetId(StateId::BraceOpen);
	auto braceCloseState = std::make_shared<TerminalState>(std::set<char> { ')' });
	braceCloseState->SetName("[)]");
	braceOpenState->SetId(StateId::BraceClose);
	auto operatorState = ConstructOperatorFSM();
	operatorState->SetName("[OP]");
	auto expressionNestedState1 = std::make_shared<RecursiveState>(expressionFsm.get());
	expressionNestedState1->SetName("[EXPR 1]");
	auto expressionNestedState2 = std::make_shared<RecursiveState>(expressionFsm.get());
	expressionNestedState2->SetName("[EXPR 2]");
	auto identifierState2 = identifierState->Clone();
	identifierState2->SetName("[ID 2]");

	auto functionCallState = ConstructFunctionCallFSM(expressionFsm.get());

	expressionFsm->AddTransition(startState, braceOpenState, 0);
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

	expressionFsm->AddTransition(startState, functionCallState, 2);
	expressionFsm->AddTransition(functionCallState, finalState, 0);

	return expressionFsm;
}

StateMachinePtr StateMachineConstructor::ConstructFunctionCallFSM(StateMachine* expressionFsm)
{
	StateMachinePtr funcCallFsm = std::make_shared<FunctionCallState>();
	funcCallFsm->SetName("[FUNC CALL]");
	auto startState = funcCallFsm->GetEntryState();
	auto finalState = funcCallFsm->GetFinalState();

	auto identifierState = ConstructIdentifierFSM();
	auto braceOpenState = std::make_shared<TerminalState>(std::set<char> { '(' });
	braceOpenState->SetId(StateId::BraceOpen);
	auto braceCloseState = std::make_shared<TerminalState>(std::set<char> { ')' });
	braceCloseState->SetId(StateId::BraceClose);
	auto expressionState = std::make_shared<RecursiveState>(expressionFsm);
	expressionState->SetName("[EXPR]");
	auto commaState = std::make_shared<TerminalState>(std::set<char> { ',' });
	commaState->SetId(StateId::Comma);

	funcCallFsm->AddTransition(startState, identifierState, 0);
	funcCallFsm->AddTransition(identifierState, braceOpenState, 0);
	funcCallFsm->AddTransition(braceOpenState, expressionState, 0);
	funcCallFsm->AddTransition(expressionState, commaState, 1);
	funcCallFsm->AddTransition(commaState, expressionState, 0);
	funcCallFsm->AddTransition(expressionState, braceCloseState, 0);
	funcCallFsm->AddTransition(braceOpenState, braceCloseState, 0);
	funcCallFsm->AddTransition(braceCloseState, finalState, 0);

	return funcCallFsm;
}

}
}
