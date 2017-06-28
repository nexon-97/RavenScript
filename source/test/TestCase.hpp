#pragma once
#include <string>
#include <memory>

namespace ravenscript
{
namespace test
{

class TestCase
{
public:
	explicit TestCase(const std::string& name)
		: m_name(name)
	{}
	virtual ~TestCase() = default;

	virtual bool Test() = 0;
	virtual void PrintResult(std::ostream& stream)
	{
		stream << "TestCase " << m_name << ": " << (m_result ? "OK." : "FAIL.") << std::endl;
	}

	std::string GetName() const { return m_name; }
	bool GetResult() const { return m_result; }

protected:
	std::string m_name;
	bool m_result = false;
};

using TestCasePtr = std::shared_ptr<TestCase>;

}
}
