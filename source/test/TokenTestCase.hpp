#pragma once
#include "TestCase.hpp"
#include "fsm/StateMachine.hpp"
#include "LexicalTokenizer.hpp"

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
		LexicalTokenizer tokenizer;
		std::vector<LexicalToken> tokensList;
		tokenizer.Parse(const_cast<char*>(m_input.c_str()), tokensList);

		LexicalToken* stream = tokensList.data();
		LexicalToken* end = tokensList.data() + tokensList.size();
		auto resultNode = m_stateMachine->Parse(stream, end, ast::NodePtr());
		m_result = !!resultNode && (stream == end);

		return m_result && stream == end;
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
