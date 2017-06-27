#pragma once
#include "StateTypes.hpp"
#include "EmptyState.hpp"

namespace ravenscript
{
namespace fsm
{

const std::string startStateName = "start";
const std::string endStateName = "end";

void StateTypes::Init()
{
	// Init special states [START], [END]
	auto startState = std::make_shared<EmptyState>();
	auto endState = std::make_shared<EmptyState>();

	m_types.insert(std::make_pair(startStateName, startState));
	m_types.insert(std::make_pair(endStateName, endState));
}

}
}
