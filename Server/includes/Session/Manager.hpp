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

namespace rtype { namespace session {

class Manager {
public:
	Manager(std::uint32_t ticks = 60); //ms
	~Manager();

	void	create(std::string const &name, int playerMax = 4);
private:
	void	_entryPoint();

	bool			_continue = true;
	std::uint32_t	_sleepTime;
	std::thread		_thread;
	//UdpListener; // UdpServer
};

}}

#endif // _SESSIONMANAGER_HPP
