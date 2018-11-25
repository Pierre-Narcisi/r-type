/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Session.hpp
*/


#if !defined(_SESSIONSESSION_HPP)
#define _SESSIONSESSION_HPP

#include <string>
#include "ClientConnection.hpp"

namespace rtype { namespace session {

class Manager;

class Session {
public:
	Session(Manager *parent, std::string const &name, int playerMax);

	void	addPlayer
private:
	std::string _id;
	std::string	_name;
	int			_playerMax;

	std::list<ClientConnection&>	_players;
}

}}


#endif // _SESSIONSESSION_HPP
