/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Game.cpp
*/

#include "Session/Session.hpp"
#include "Session/Game.hpp"

namespace rtype { namespace session {

void	Game::init() {
	_ecs = &ecs::Ecs::get();
	//init all Components
}

void	Game::_initSystems() {
	//init all systems
}

void	Game::update() {
	_ecs->update();
}

void	Game::onKeyPress(ID player, proto::KeyPress &packet) {

}

void	Game::onKeyRelease(ID player, proto::KeyRelease &packet) {

}

}}