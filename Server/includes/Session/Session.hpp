
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
#include "Event/HdlCollector.hpp"
#include "ClientConnection.hpp"

namespace rtype { namespace session {

class Manager;

class Session {
public:
	explicit Session(Manager *parent, std::uint32_t id, std::string const &name, int playerMax);
	~Session();

	void	addPlayer(ClientConnection &player);

	void	addTask(std::function<void()> const &task);
private:
	void			_entryPoint();

	Manager			*_parent;
	std::uint32_t	_id;
	std::string		_name;
	int				_playerMax;

	bool								_continue = true;
	std::unique_ptr<std::thread>		_thread;
	std::deque<std::function<void()>>	_pool;
	std::mutex							_poolLock;
	std::mutex							_pickLock;

	evt::HdlCollector				_collector;
	std::list<ClientConnection*>	_players;
	std::mutex						_addPlayerMutex;

	struct DestContainer {
		~DestContainer() {
			std::cout << "~Dest" << std::endl;
		}
		evt::Event::EvtHdlDestr	dest;
	};

	std::list<DestContainer>	_destList;

	friend Manager;
};

}}


#endif // _SESSIONSESSION_HPP
