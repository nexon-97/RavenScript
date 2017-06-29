#pragma once
#include "TestCase.hpp"
#include "fsm/StateMachine.hpp"
#include "LexicalTokenizer.hpp"

namespace ravenscript
{
namespace test
{

class OperatorTestCase : public TestCase
{
public:
	explicit OperatorTestCase(const std::string& name, const std::string& input, const fsm::StateMachinePtr& stateMachine)
		: TestCase(name)
		, m_input(input)
		, m_stateMachine(stateMachine)
	{}
	virtual ~OperatorTestCase() = default;

	virtual bool Test() override
	{
		LexicalTokenizer tokenizer;
		std::vector<LexicalToken> tokensList;
		tokenizer.Parse(const_cast<char*>(m_input.c_str()), tokensList);

		LexicalToken* stream = tokensList.data();
		LexicalToken* end = tokensList.data() + tokensList.size();
		m_result = m_stateMachine->Parse(stream, end);

		return m_result;
	}

	virtual void PrintResult(std::ostream& stream) override
	{
		stream << "[" << m_name << "] " << m_input << " is valid operator? " << (m_result ? "OK." : "FAIL.") << std::endl;
	}

protected:
	std::string m_input;
	fsm::StateMachinePtr m_stateMachine;
};

}
}
