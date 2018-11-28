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
#include <mutex>
#include <unordered_map>
#include "Session/Session.hpp"
#include "Network/UdpSocket/UdpSocket.hpp"

namespace rtype { namespace session {

class Manager {
public:
	Manager(std::uint32_t ticks = 60); //ms
	~Manager();

	Session	&create(std::string const &name, int playerMax = 4);

	auto	&getSessions() { return _sessions; }
	auto	getListeningPort() { return _port; }
private:
	void			_entryPoint();
	std::uint32_t	_generateId();

	bool							_continue = true;
	std::uint32_t					_sleepTime;
	std::unique_ptr<std::thread>	_thread;
	std::list<Session>				_sessions;
	nw::UdpSocket					_sock;
	std::uint16_t					_port;
};

}}

#endif // _SESSIONMANAGER_HPP
