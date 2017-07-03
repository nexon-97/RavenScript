#include <iostream>
#include <sstream>

#include "Interpreter.hpp"
#include "fsm/TerminalState.hpp"
#include "fsm/StateMachineConstructor.hpp"

#include "test/IdentifierTestSuite.hpp"
#include "test/ExpressionTestSuite.hpp"
#include "test/OperatorTestSuite.hpp"

const int VERSION_MAJOR = 0;
const int VERSION_MINOR = 1;

std::string GetVersionString();

int main(int argc, char** argv)
{
	std::cout << "RavenScript " << GetVersionString() << std::endl;

	//auto interpreter = ravenscript::Interpreter();
	//interpreter.DoFile("script\\init.rs");

	using namespace ravenscript::fsm;
	using namespace ravenscript::test;
	
	// Perform unit testing
	//IdentifierTestSuite identifierTestSuite;
	//identifierTestSuite.Test(std::cout);

	//OperatorTestSuite operatorTestSuite;
	//operatorTestSuite.Test(std::cout);

	ExpressionTestSuite expressionTestSuite;
	expressionTestSuite.Test(std::cout);

	system("pause");
	return 0;
}

std::string GetVersionString()
{
	std::stringstream ss;
	ss << "v." << VERSION_MAJOR << '.' << VERSION_MINOR;

	return ss.str();
}
