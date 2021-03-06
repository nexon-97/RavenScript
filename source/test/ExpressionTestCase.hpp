#pragma once
#include "TestCase.hpp"
#include "fsm/StateMachine.hpp"
#include "LexicalTokenizer.hpp"
#include "ast/PriorityAligner.hpp"

namespace ravenscript
{
namespace test
{

class ExpressionTestCase : public TestCase
{
public:
	explicit ExpressionTestCase(const std::string& name, const std::string& input, const fsm::StateMachinePtr& stateMachine)
		: TestCase(name)
		, m_input(input)
		, m_stateMachine(stateMachine)
	{}
	virtual ~ExpressionTestCase() = default;

	virtual bool Test() override
	{
		LexicalTokenizer tokenizer;
		std::vector<LexicalToken> tokensList;
		tokenizer.Parse(const_cast<char*>(m_input.c_str()), tokensList);

		LexicalToken* stream = tokensList.data();
		LexicalToken* end = tokensList.data() + tokensList.size();
		m_resultNode = m_stateMachine->Parse(stream, end, ast::NodePtr());
		m_result = !!m_resultNode && (stream == end);

		return m_result;
	}

	virtual void PrintResult(std::ostream& stream) override
	{
		stream << m_input << " is valid expression: " << (m_result ? "OK." : "FAIL.") << std::endl;
		if (m_result)
		{
			m_resultNode = m_resultNode->Align();
			m_resultNode->Print(stream, 0);
		}
	}

protected:
	std::string m_input;
	fsm::StateMachinePtr m_stateMachine;
	ast::NodePtr m_resultNode;
};

}
}
