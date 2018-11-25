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
	_sleepTime(1000 / ticks),
	_thread(std::bind(&Manager::_entryPoint, this)) {}

Manager::~Manager() {
	_continue = false;
	_thread.join();
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

}}
