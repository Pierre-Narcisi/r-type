/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Session.cpp
*/

#include "Session/Session.hpp"

namespace rtype { namespace session {

Session::Session(Manager *parent, std::uint32_t id, std::string const &name, int playerMax):
		_parent(parent),
		_id(id),
		_name(name),
		_playerMax(playerMax),
		_thread(std::bind(&Session::_entryPoint, this)) {}

Session::~Session() {
	_continue = false;
	_thread.join();
}

void	Session::_entryPoint() {
	while (_continue) {
		decltype(_pool)::iterator	it;
		{
			std::lock_guard<std::mutex>	_guard(_pickLock);

			it = _pool.begin();
		}

		{
			std::lock_guard<std::mutex>	_guard(_pickLock);

			_pool.erase(it);
		}
	}
}

void	Session::addPlayer(ClientConnection &player) {
	std::lock_guard<std::mutex>	_guard(_addPlayerMutex);

	_players.push_back(&player);
	auto it = _players.end();
	it--;
	_collector << player.onDestroy.addHandler([this, it] {
		_players.erase(it);
	});
}

void	Session::addTask(std::function<void()> const &task) {
	std::lock_guard<std::mutex>	_guard(_pickLock);

	_pool.push(task);
}

}}