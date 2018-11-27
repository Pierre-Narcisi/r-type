/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Session.cpp
*/

#include <functional>
#include "Session/Session.hpp"
#include "Event/Manager.hpp"

namespace rtype { namespace session {

Session::Session(Manager *parent, std::uint32_t id, std::string const &name, int playerMax):
		_parent(parent),
		_id(id),
		_name(name),
		_playerMax(playerMax) {
	_thread = std::unique_ptr<std::thread>(new std::thread(&Session::_entryPoint, this)); // Force start after mutex init

	evt::Manager::get()["onPlayerDisconnect"]->addHandler<void, ClientConnection&>([this] (ClientConnection &clt) {
		for (auto it = _players.begin(); it != _players.end(); ++it) {
			if (*it == &clt) {
				_players.erase(it);
				return;
			}
		}
	});
}

Session::~Session() {
	_continue = false;
	_poolLock.unlock();
	_thread->join();
}

void	Session::_entryPoint() {
	_poolLock.lock(); //Have to lock when _pool is empty, addTask will delock the pool

	while (_continue) {
		_poolLock.lock(); //if already lock, it wait for a new task
		_poolLock.unlock();

		if (!_continue) return;

		decltype(_pool)::iterator	it;
		{
			std::lock_guard<std::mutex>	_guard(_pickLock);

			it = _pool.begin();
		}

		(*it)(); //Launch Task

		{
			std::lock_guard<std::mutex>	_guard(_pickLock);

			_pool.erase(it);

			if (_pool.size() == 0)
				_poolLock.lock(); //lock if empty
		}
	}
}

void	Session::addPlayer(ClientConnection &player) {
	std::lock_guard<std::mutex>	_guard(_addPlayerMutex);

	_players.push_back(&player);
}

void	Session::_rmPlayer(decltype(_players)::iterator player) {
	_players.erase(player);
}

void	Session::addTask(std::function<void()> const &task) {
	std::lock_guard<std::mutex>	_guard(_pickLock);

	_pool.push_back(task);
	_poolLock.unlock();
}

}}