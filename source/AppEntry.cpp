#include <iostream>
#include <sstream>

#include "Interpreter.hpp"
#include "fsm/StateMachineDesc.hpp"
#include "fsm/StateTypes.hpp"
#include "fsm/TerminalState.hpp"

const int VERSION_MAJOR = 0;
const int VERSION_MINOR = 1;

std::string GetVersionString();

int main(int argc, char** argv)
{
	std::cout << "RavenScript " << GetVersionString() << std::endl;

	auto interpreter = ravenscript::Interpreter();
	interpreter.DoFile("script\\init.rs");

	/*ravenscript::fsm::StateMachineDesc fsmDesc;
	fsmDesc.LoadFromFile("fsm_data\\fsm_descriptions.xml", "identifier");

	if (StateTypes::HasInstance())
	{
		StateTypes::FreeInstance();
	}*/

	using namespace ravenscript::fsm;

	std::set<char> digits = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	std::set<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_' };

	// Test fsm
	StateMachinePtr testFsm = std::make_shared<StateMachine>();
	auto startState = testFsm->GetEntryState();
	auto finalState = testFsm->GetFinalState();

	auto letterState = std::make_shared<TerminalState>(letters);
	auto digitState = std::make_shared<TerminalState>(digits);
	testFsm->AddState(letterState);
	testFsm->AddState(digitState);

	testFsm->AddTransition(startState, letterState);
	testFsm->AddTransition(letterState, digitState);
	testFsm->AddTransition(digitState, letterState);
	testFsm->AddTransition(letterState, finalState);
	testFsm->AddTransition(digitState, finalState);
	testFsm->AddTransition(letterState, letterState);
	testFsm->AddTransition(digitState, digitState);

	const char* testString1 = "_lol25kek";
	const char* testString2 = "25kek";
	char* str1Iterator = const_cast<char*>(testString1);
	char* str2Iterator = const_cast<char*>(testString2);
	bool parseResult1 = testFsm->Parse(&str1Iterator);
	bool parseResult2 = testFsm->Parse(&str2Iterator);

	std::cout << testString1 << " is [IDENTIFIER]: " << (parseResult1 ? "+" : "-") << std::endl;
	std::cout << testString2 << " is [IDENTIFIER]: " << (parseResult2 ? "+" : "-") << std::endl;

	system("pause");
	return 0;
}

std::string GetVersionString()
{
	std::stringstream ss;
	ss << "v." << VERSION_MAJOR << '.' << VERSION_MINOR;

	return ss.str();
}
