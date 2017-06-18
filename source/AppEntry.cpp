#include <iostream>
#include <sstream>

#include "Interpreter.hpp"

const int VERSION_MAJOR = 0;
const int VERSION_MINOR = 1;

std::string GetVersionString();

int main(int argc, char** argv)
{
	std::cout << "RavenScript " << GetVersionString() << std::endl;

	auto interpreter = ravenscript::Interpreter();
	interpreter.DoFile("script\\init.rs");

	system("pause");
	return 0;
}

std::string GetVersionString()
{
	std::stringstream ss;
	ss << "v." << VERSION_MAJOR << '.' << VERSION_MINOR;

	return ss.str();
}
