
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
	Manager			*_parent;
	std::uint32_t		_id;
	std::string		_name;
	int			_playerMax;

	bool					_continue = true;
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

	void	sendCreate(ID id);

	json::Entity	getActualSheet() {
		std::lock_guard<std::mutex>	_guard(_sheetMtx);

		return _sheet;
	}

	auto	&getPlayers() { return _players; }

	void 	sendToPlayers(proto::PacketBase const &packet, std::size_t size);
	void 	sendToPlayer(ClientConnection *player, proto::PacketBase const &packet, std::size_t size);
private:
	void	_entryPoint();

	struct PlayerContainer {
		ClientConnection	*player;
		bool				isDeleted = false;
		ID					ecsId;
	};

	std::list<PlayerContainer>	_players;
	Game						_game;

	std::mutex					_sheetMtx;
	json::Entity				_sheet;
	std::uint32_t				_sleepTime = 1000 / 60;

	void	_rmPlayer(decltype(_players)::iterator player);

	friend Manager;
	friend Game;
	friend ::rtype::Server;
};

}}


#endif // _SESSIONSESSION_HPP
