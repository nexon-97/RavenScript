#pragma once
#include "TestCase.hpp"
#include <vector>

namespace ravenscript
{
namespace test
{

class TestSuite
{
public:
	TestSuite() = default;
	virtual ~TestSuite() = default;

	virtual void SetUp() {}
	virtual void CleanUp() {}

	void RegisterTestCase(const TestCasePtr& testCase);

	void Test(std::ostream& stream);

protected:
	std::vector<TestCasePtr> m_testCases;
	std::string m_input;
	bool m_result = false;
};

}
}
