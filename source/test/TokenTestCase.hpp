#pragma once
#include "TestCase.hpp"
#include "fsm/StateMachine.hpp"

namespace ravenscript
{
namespace test
{

class TokenTestCase : public TestCase
{
public:
	explicit TokenTestCase(const std::string& name, const std::string& input, const fsm::StateMachinePtr& stateMachine)
		: TestCase(name)
		, m_input(input)
		, m_stateMachine(stateMachine)
	{}
	virtual ~TokenTestCase() = default;

	virtual bool Test() override
	{
		char* strIterator = const_cast<char*>(m_input.c_str());
		m_result = m_stateMachine->Parse(&strIterator);

		return m_result;
	}

	virtual void PrintResult(std::ostream& stream) override
	{
		stream << m_input << " is valid token: " << (m_result ? "OK." : "FAIL.") << std::endl;
	}

protected:
	std::string m_input;
	fsm::StateMachinePtr m_stateMachine;
};

}
}
