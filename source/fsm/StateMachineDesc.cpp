#include "StateMachineDesc.hpp"
#include "Utils.hpp"
#include "StateTypes.hpp"
#include <cassert>

namespace ravenscript
{
namespace fsm
{

bool StateMachineDesc::LoadFromFile(const char* path, const char* fsmId)
{
	auto document = utils::LoadXmlFile(path);
	if (!!document)
	{
		auto root = document->RootElement();

		if (!StateTypes::HasInstance())
		{
			auto stateTypes = new StateTypes();
			stateTypes->Init();
		}

		// Load fsm nodes
		for (auto fsmNode = root->FirstChildElement("fsm"); !!fsmNode; fsmNode = fsmNode->NextSiblingElement())
		{
			const char* fsmId = fsmNode->Attribute("id");
			if (!!fsmId && strcmp(fsmId, fsmId) == 0)
			{
				// Fsm with given id found, load it
				m_id = std::string(fsmId);

				auto statesNode = fsmNode->FirstChildElement("states");
				auto transitionsNode = fsmNode->FirstChildElement("transitions");

				return (!!statesNode && !!transitionsNode) && LoadStates(statesNode) && LoadTransitions(transitionsNode);
			}
		}

		return false;
	}

	return false;
}

bool StateMachineDesc::SaveToFile(const char* path)
{
	// Not implemented yet
	return false;
}

bool StateMachineDesc::LoadStates(tinyxml2::XMLElement* element)
{
	m_states.emplace(std::make_pair(std::string("start"), StateInfo("start", nullptr, std::string())));
	m_states.emplace(std::make_pair(std::string("end"), StateInfo("end", nullptr, std::string())));

	for (auto stateNode = element->FirstChildElement("state"); !!stateNode; stateNode = stateNode->NextSiblingElement())
	{
		std::string id = utils::ValueOrEmpty(stateNode->Attribute("id"));
		std::string value = utils::ValueOrEmpty(stateNode->Attribute("value"));
			
		m_states.emplace(std::make_pair(std::string(id), StateInfo(id, nullptr, value)));
	}

	return true;
}

bool StateMachineDesc::LoadTransitions(tinyxml2::XMLElement* element)
{
	for (auto transitionNode = element->FirstChildElement("transition"); !!transitionNode; transitionNode = transitionNode->NextSiblingElement())
	{
		bool bidirectional = transitionNode->BoolAttribute("bidirectional");
		std::string fromId = utils::ValueOrEmpty(transitionNode->Attribute("from"));
		std::string toId = utils::ValueOrEmpty(transitionNode->Attribute("to"));
		
		auto fromIt = m_states.find(fromId);
		auto toIt = m_states.find(toId);

		StateInfo* from = (fromIt != m_states.end()) ? &fromIt->second : nullptr;
		StateInfo* to = (toIt != m_states.end()) ? &toIt->second : nullptr;

		assert(!!from);
		assert(!!to);

		m_transitions.emplace_back(from, to, bidirectional);
	}

	return true;
}

}
}
