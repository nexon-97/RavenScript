#pragma once
#include <vector>
#include <map>
#include "tinyxml2/tinyxml2.h"

namespace ravenscript
{
namespace fsm
{

class StateMachineDesc
{
public:
	struct StateType
	{
		std::string id;
		bool isTerminal;

		explicit StateType(const std::string& id, bool isTerminal)
			: id(id)
			, isTerminal(isTerminal)
		{}
	};

	struct StateInfo
	{
		std::string id;
		StateType* stateType;
		std::string value;

		explicit StateInfo(const std::string& id, StateType* stateType, const std::string& value)
			: id(id)
			, stateType(stateType)
			, value(value)
		{}
	};

	struct TransitionInfo
	{
		StateInfo* from;
		StateInfo* to;
		bool bidirectional;

		explicit TransitionInfo(StateInfo* from, StateInfo* to, bool bidirectional)
			: from(from)
			, to(to)
			, bidirectional(bidirectional)
		{}
	};

public:
	StateMachineDesc() = default;
	virtual ~StateMachineDesc() = default;

	bool LoadFromFile(const char* path, const char* fsmId);
	bool SaveToFile(const char* path);

	const std::string& GetId() const { return m_id; }
	const std::map<std::string, StateInfo>& GetStates() const { return m_states; }
	const std::vector<TransitionInfo>& GetTransitions() const { return m_transitions; }

protected:
	bool LoadStates(tinyxml2::XMLElement* element);
	bool LoadTransitions(tinyxml2::XMLElement* element);

protected:
	std::string m_id;
	std::map<std::string, StateType> m_stateTypes;
	std::map<std::string, StateInfo> m_states;
	std::vector<TransitionInfo> m_transitions;
};

}
}
