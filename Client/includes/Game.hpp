/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Game.hpp
*/

#if !defined(_GAMECLIENT_HPP)
#define _GAMECLIENT_HPP

#include "ServerConnection.hpp"

namespace rtype {

class Game {
public:
	Game() = default;

	void	start(ServerConnection &srv);
};

}

#endif // _GAMECLIENT_HPP
