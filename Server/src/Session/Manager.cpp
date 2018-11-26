/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Manager.cpp
*/

#include <functional>
#include <mutex>
#include <chrono>
#include "Session/Manager.hpp"

namespace rtype { namespace session {

Manager::Manager(std::uint32_t ticks):
		_sleepTime(1000 / ticks) {
	_thread = std::unique_ptr<std::thread>(new std::thread(&Manager::_entryPoint, this)); // Force start after mutex init
}

Manager::~Manager() {
	_continue = false;
	_thread->join();

}

void	Manager::_entryPoint() {
	while (_continue) {
		
		std::this_thread::sleep_for(std::chrono::milliseconds(_sleepTime));
	}
}

static std::mutex	_generateIdMutex;
inline std::uint32_t	Manager::_generateId() {
	std::lock_guard<std::mutex>	_guard(_generateIdMutex);
	static std::uint32_t	counter = 0;

	return ++counter;
}

Session	&Manager::create(std::string const &name, int playerMax) {
	for (auto &s: _sessions) {
		if (s._name == name) {
			throw std::runtime_error("Name already in use");
		}
	}

	return _sessions.emplace_back(this, _generateId(), name, playerMax);
}

}}
