
/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Session.hpp
*/


#if !defined(_SESSIONSESSION_HPP)
#define _SESSIONSESSION_HPP

#include <string>
#include <deque>
#include <mutex>
#include <thread>
#include "GameEngine/ecs/Entity.hpp"
#include "Event/HdlCollector.hpp"
#include "Network/GameProtocol.hpp"
#include "ClientConnection.hpp"
#include "Game.hpp"

namespace rtype { namespace session {

class Manager;

class Session {
private:
	void			_entryPoint();

	Manager			*_parent;
	std::uint32_t	_id;
	std::string		_name;
	int				_playerMax;

	bool								_continue = true;
	std::unique_ptr<std::thread>		_thread;
	std::deque<std::function<std::shared_ptr<proto::PacketBase>()>>
										_pool;
	std::mutex							_pickLock;

	evt::HdlCollector				_collector;
	std::mutex						_addPlayerMutex;
public:
	explicit Session(Manager *parent, std::uint32_t id, std::string const &name, int playerMax);
	~Session();

	void	addPlayer(ClientConnection &player);

	void	addTask(decltype(_pool)::value_type const &task);

	auto	getId() { return _id; }
private:

	struct PlayerContainer {
		ClientConnection	*player;
		ID					ecsId;
	};

	std::list<PlayerContainer>	_players;
	Game						_game;

	void	_rmPlayer(decltype(_players)::iterator player);

	friend Manager;
	friend ::rtype::Server;
};

}}


#endif // _SESSIONSESSION_HPP
