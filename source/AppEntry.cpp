#include <iostream>
#include <sstream>

#include "Interpreter.hpp"
#include "fsm/StateMachineDesc.hpp"
#include "fsm/StateTypes.hpp"
#include "fsm/TerminalState.hpp"

#include "test/IdentifierTestSuite.hpp"

const int VERSION_MAJOR = 0;
const int VERSION_MINOR = 1;

std::string GetVersionString();
ravenscript::fsm::StateMachinePtr ConstructIdentifierFSM();
ravenscript::fsm::StateMachinePtr ConstructOperatorFSM();

int main(int argc, char** argv)
{
	std::cout << "RavenScript " << GetVersionString() << std::endl;

	auto interpreter = ravenscript::Interpreter();
	interpreter.DoFile("script\\init.rs");

	using namespace ravenscript::fsm;
	using namespace ravenscript::test;
	
	// Perform unit testing
	IdentifierTestSuite identifierTestSuite;
	identifierTestSuite.Test(std::cout);

	// Construct identifier fsm
	StateMachinePtr identifierFsm = ConstructIdentifierFSM();
	StateMachinePtr operatorFsm = ConstructOperatorFSM();

	const char* testString3 = "testVar = 25";
	const char* testString4 = ".";
	char* str3Iterator = const_cast<char*>(testString3);
	char* str4Iterator = const_cast<char*>(testString4);
	bool parseResult3 = identifierFsm->Parse(&str3Iterator);
	bool parseResult4 = operatorFsm->Parse(&str4Iterator);

	std::cout << testString3 << " is [STATEMENT]: " << (parseResult3 ? "+" : "-") << std::endl;
	std::cout << testString4 << " is [OPERATOR]: " << (parseResult4 ? "+" : "-") << std::endl;

	system("pause");
	return 0;
}

ravenscript::fsm::StateMachinePtr ConstructIdentifierFSM()
{
	using namespace ravenscript::fsm;

	std::set<char> digits = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	std::set<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_' };

	StateMachinePtr identifierFsm = std::make_shared<StateMachine>();
	auto startState = identifierFsm->GetEntryState();
	auto finalState = identifierFsm->GetFinalState();

	auto letterState = std::make_shared<TerminalState>(letters);
	auto digitState = std::make_shared<TerminalState>(digits);
	identifierFsm->AddState(letterState);
	identifierFsm->AddState(digitState);

	identifierFsm->AddTransition(startState, letterState);
	identifierFsm->AddTransition(letterState, digitState);
	identifierFsm->AddTransition(digitState, letterState);
	identifierFsm->AddTransition(letterState, finalState);
	identifierFsm->AddTransition(digitState, finalState);
	identifierFsm->AddTransition(letterState, letterState);
	identifierFsm->AddTransition(digitState, digitState);

	return identifierFsm;
}

ravenscript::fsm::StateMachinePtr ConstructOperatorFSM()
{
	using namespace ravenscript::fsm;

	StateMachinePtr operatorFsm = std::make_shared<StateMachine>();
	auto startState = operatorFsm->GetEntryState();
	auto finalState = operatorFsm->GetFinalState();

	auto dotState = std::make_shared<TerminalState>(std::set<char> { '.' });
	auto assignmentState = std::make_shared<TerminalState>(std::set<char> { '=' });
	operatorFsm->AddState(dotState);
	operatorFsm->AddState(assignmentState);

	operatorFsm->AddTransition(startState, dotState);
	operatorFsm->AddTransition(startState, assignmentState);
	operatorFsm->AddTransition(dotState, finalState);
	operatorFsm->AddTransition(assignmentState, finalState);

	return operatorFsm;
}

std::string GetVersionString()
{
	std::stringstream ss;
	ss << "v." << VERSION_MAJOR << '.' << VERSION_MINOR;

	return ss.str();
}
