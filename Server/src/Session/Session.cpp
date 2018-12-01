/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Session.cpp
*/

#define NOSPRITE
#include <functional>
#include <component/graphical/Drawable.hpp>
#include <component/physic/Hitbox.hpp>
#include <component/online/OnlineComponent.hpp>
#include <component/control/DeplacementKeyBoard.hpp>
#include "Event/Manager.hpp"
#include "GameEngine/ecs/Ecs.hpp"
#include "GameEngine/core/Time.hpp"
#include "GameEngine/component/physic/Position.hpp"
#include "Network/GameProtocol.hpp"
#include "Session/Manager.hpp"
#include "Session/Session.hpp"
#undef NOSPRITE

namespace rtype { namespace session {

Session::Session(Manager *parent, std::uint32_t id, std::string const &name, int playerMax):
		_parent(parent),
		_id(id),
		_name(name),
		_playerMax(playerMax),
		_game(*this) {
	_thread = std::unique_ptr<std::thread>(new std::thread(&Session::_entryPoint, this)); // Force start after mutex init

	_collector << evt::Manager::get()["onPlayerDisconnect"]->addHandler<void, ClientConnection&>([this] (ClientConnection &clt) {
		for (auto it = _players.begin(); it != _players.end(); ++it) {
			if (it->player == &clt) {
				_rmPlayer(it);
				return;
			}
		}
	});
}

Session::~Session() {
	_continue = false;
	_thread->join();
}


void 	Session::sendToPlayers(proto::PacketBase const &packet, std::size_t size) {
	nw::UdpBuffer	wbuf{const_cast<char*>(reinterpret_cast<const char*>(&packet)), size};

	for (auto &playerW: _players) {
		auto &ep = playerW.player->_udpEndpoint;

		_parent->getUdpSocket().sendTo(wbuf, ep);
	}
}

void 	Session::sendToPlayer(ClientConnection *player, proto::PacketBase const &packet, std::size_t size) {
	nw::UdpBuffer	wbuf{const_cast<char*>(reinterpret_cast<const char*>(&packet)), size};

	for (auto &playerW: _players) {
		if (playerW.player == player) {
			auto &ep = playerW.player->_udpEndpoint;

			_parent->getUdpSocket().sendTo(wbuf, ep);
			return;
		}
	}
}


void	Session::_entryPoint() {
	_game.init();
	while (_continue) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		decltype(_pool)::value_type	nextPacket;
		while (true) {
			{
				std::lock_guard<std::mutex>	_guard(_pickLock);
				auto it = _pool.begin();

				if (it != _pool.end()) {
					nextPacket = *it;
					_pool.erase(it);
				} else {
					break;
				}
			}

			auto	packet = nextPacket();

			if (packet.get() != nullptr) {
				auto			playerId = packet->playerId();
				PlayerContainer		*cont = nullptr;

				for (auto &clt: _players) {
					if (clt.player->_status.id == playerId) {
						cont = &clt;
						break;
					}
				}


				if (cont != nullptr) {
					switch (packet->type) {
						case proto::Type::KEYPRESS:
							_game.onKeyPress(playerId, cont->ecsId, *reinterpret_cast<proto::KeyPress*>(packet.get()));
							break;
						case proto::Type::KEYRELEASE:
							_game.onKeyRelease(playerId, cont->ecsId, *reinterpret_cast<proto::KeyRelease*>(packet.get()));
							break;
						default:
							break;
					}
				}
			}
		}
		_game.update();


		auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(x));
	}
}

void	Session::addPlayer(ClientConnection &player) {
	std::lock_guard<std::mutex>	_guard(_addPlayerMutex);


	auto cont = _players.insert(_players.end(), {&player, (ID)0});
	addTask([this, cont] () {
		auto	&ecs = ecs::Ecs::get();

		auto ids = ecs::Ecs::filter<ecs::component::Position, ecs::component::Hitbox, ecs::component::OnlineComponent>();
		auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		auto &hitbox = ecs::Ecs::getComponentMap<ecs::component::Hitbox>();
		auto &online = ecs::Ecs::getComponentMap<ecs::component::OnlineComponent>();
		for (auto id: ids) {
			proto::Create	pack{
				proto::Type::CREATE, _id, 0, id,
				hitbox[id].width, hitbox[id].height,
				pos[id].x, pos[id].y,
				online[id].spriteId
			};

			sendToPlayer(cont->player, reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
		}

		ID id = ecs::entity::Entity::getId();

		ecs::Ecs::addComponent<ecs::component::Position>(id, 50, 50);
		ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100.f, 100.f);
		ecs::Ecs::addComponent<ecs::component::OnlineComponent>(id, id, 1);
		ecs::Ecs::addComponent<ecs::component::Keyboard>(id);
		ecs::Ecs::addComponent<ecs::component::DeplacementKeyBoard>(id);

		cont->ecsId = id;

		proto::Create	pack{proto::Type::CREATE, _id, 0, id, 100, 100, 50, 50, 1};
		sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));

		return std::shared_ptr<proto::PacketBase>(nullptr);
	});
}

void	Session::_rmPlayer(decltype(_players)::iterator player) {
	addTask([this, player] () {
		std::lock_guard<std::mutex>	_guard(_addPlayerMutex);

		ecs::Ecs::deleteId(player->ecsId);
		_players.erase(player);
		return std::shared_ptr<proto::PacketBase>(nullptr);
	});
}

void	Session::addTask(decltype(_pool)::value_type const &task) {
	std::lock_guard<std::mutex>	_guard(_pickLock);

	_pool.push_back(task);
}

}}