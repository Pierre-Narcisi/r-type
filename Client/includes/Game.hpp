/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Game.hpp
*/

#if !defined(_GAMECLIENT_HPP)
#define _GAMECLIENT_HPP

#include "component/control/Keyboard.hpp"
#include "ServerConnection.hpp"

namespace rtype {

class Game {
public:
	Game() = default;

	void	start(ServerConnection &srv);
private:
	void	_onReceiveMove(proto::Move &packet);
	void	_onReceiveCreate(proto::Create &packet);
	void	_onReceiveDelete(proto::Delete &packet);

	template <KeyKeyboard KEY>
	void 	_keyboardFactory(ID keyboard, ServerConnection &srv);
};

}

#endif // _GAMECLIENT_HPP
