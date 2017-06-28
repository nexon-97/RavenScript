#include "TestSuite.hpp"

namespace ravenscript
{
namespace test
{

void TestSuite::Test(std::ostream& stream)
{
	SetUp();

	for (TestCasePtr testCase : m_testCases)
	{
		testCase->Test();
		testCase->PrintResult(stream);
	}

	CleanUp();
}

void TestSuite::RegisterTestCase(const TestCasePtr& testCase)
{
	m_testCases.push_back(testCase);
}

}
}
