/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Manager.hpp
*/


#if !defined(_SESSIONMANAGER_HPP)
#define _SESSIONMANAGER_HPP

#include <cstddef>
#include <string>
#include <thread>
#include <unordered_map>
#include "Session/Session.hpp"

namespace rtype { namespace session {

class Manager {
public:
	Manager(std::uint32_t ticks = 60); //ms
	~Manager();

	Session	&create(std::string const &name, int playerMax = 4);

	auto	&getSessions() { return _sessions; }
private:
	void			_entryPoint();
	std::uint32_t	_generateId();

	bool							_continue = true;
	std::uint32_t					_sleepTime;
	std::unique_ptr<std::thread>	_thread;
	std::list<Session>				_sessions;
	//UdpListener; // UdpServer
};

}}

#endif // _SESSIONMANAGER_HPP
