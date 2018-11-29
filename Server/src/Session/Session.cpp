/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Session.cpp
*/

#include <functional>
#include "Event/Manager.hpp"
#include "GameEngine/ecs/Ecs.hpp"
#include "GameEngine/core/Time.hpp"
#include "GameEngine/component/physic/Position.hpp"
#include "Network/GameProtocol.hpp"
#include "Session/Session.hpp"

namespace rtype { namespace session {

Session::Session(Manager *parent, std::uint32_t id, std::string const &name, int playerMax):
		_parent(parent),
		_id(id),
		_name(name),
		_playerMax(playerMax) {
	_thread = std::unique_ptr<std::thread>(new std::thread(&Session::_entryPoint, this)); // Force start after mutex init

	evt::Manager::get()["onPlayerDisconnect"]->addHandler<void, ClientConnection&>([this] (ClientConnection &clt) {
		for (auto it = _players.begin(); it != _players.end(); ++it) {
			if (it->player == &clt) {
				_players.erase(it);
				return;
			}
		}
	});
}

Session::~Session() {
	_continue = false;
	_thread->join();
}

void	Session::_entryPoint() {
	auto	&ecs = ecs::Ecs::get();

	// std::cout << "Ecs ptr: " << (void*) &ecs << std::endl;
	while (_continue) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		decltype(_pool)::value_type	fct;
		{
			std::lock_guard<std::mutex>	_guard(_pickLock);
			auto it = _pool.begin();

			if (it != _pool.end()) {
				fct = *it;
				_pool.erase(it);
			}
		}

		if (fct != nullptr) {
			auto packet = fct();

			if (packet != nullptr) {
				switch (packet->type) {
					case proto::Type::KEYPRESS: break;
					case proto::Type::KEYRELEASE: break;
				}
			}
		}
		ecs.update();

		auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(x));
	}
}

void	Session::addPlayer(ClientConnection &player) {
	std::lock_guard<std::mutex>	_guard(_addPlayerMutex);


	auto cont = _players.insert(_players.end(), {&player, (ID)0});
	addTask([this, cont] () {
		auto	&ecs = ecs::Ecs::get();

		std::cout << "Ecs ptr: " << (void*) &ecs << std::endl;
		ID id = ecs::entity::Entity::getId();
		ecs::Ecs::addComponent<ecs::component::Position>(id);

		cont->ecsId = id;
		return std::shared_ptr<proto::PacketBase>(nullptr);
	});
}

void	Session::_rmPlayer(decltype(_players)::iterator player) {
	std::lock_guard<std::mutex>	_guard(_addPlayerMutex);

	_players.erase(player);
}

void	Session::addTask(decltype(_pool)::value_type const &task) {
	std::lock_guard<std::mutex>	_guard(_pickLock);

	_pool.push_back(task);
}

}}