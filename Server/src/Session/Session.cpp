/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Session.cpp
*/

#define NOSPRITE
#include <functional>
#include <Server/src/Session/components/Firerate.hpp>
#include "Session/components/Inventory.hpp"
#include "Session/systems/Fire.hpp"
#include "component/graphical/Drawable.hpp"
#include "component/physic/Hitbox.hpp"
#include "component/online/OnlineComponent.hpp"
#include "component/control/DeplacementKeyBoard.hpp"
#include "component/physic/Speed.hpp"
#include "Event/Manager.hpp"
#include "GameEngine/ecs/Ecs.hpp"
#include "GameEngine/core/Time.hpp"
#include "GameEngine/component/physic/Position.hpp"
#include "Session/components/Types.hpp"
#include "Network/GameProtocol.hpp"
#include "Session/Manager.hpp"
#include "Session/Session.hpp"
#include "GameEngine/TimedEvent/TimedEventAdmin.hpp"
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
	nw::UdpBuffer	wbuf{
		const_cast<char*>(reinterpret_cast<const char*>(&packet)),
		size
	};
	//std::lock_guard<std::mutex>	_guard(_addPlayerMutex);

	for (auto &playerW: _players) {
		if (playerW.isDeleted == false) {
			auto	&ep = playerW.player->_udpEndpoint;

			_parent->getUdpSocket().sendTo(wbuf, ep);
		}
	}
}

void 	Session::sendToPlayer(ClientConnection *player, proto::PacketBase const &packet, std::size_t size) {
	nw::UdpBuffer				wbuf{
		const_cast<char*>(reinterpret_cast<const char*>(&packet)),
		size
	};
	//std::lock_guard<std::mutex>	_guard(_addPlayerMutex);

	for (auto &playerW: _players) {
		if (playerW.player == player) {
			if (playerW.isDeleted == false) {
				auto	&ep = playerW.player->_udpEndpoint;

				_parent->getUdpSocket().sendTo(wbuf, ep);
			}
			return;
		}
	}
}


void	Session::_entryPoint() {
	_game.init();
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

	while (_continue) {
		start = std::chrono::high_resolution_clock::now();
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

		// auto ids = ecs::Ecs::filter<ecs::component::Position, ecs::component::Hitbox, ecs::component::OnlineComponent>();
		// auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		// auto &hitbox = ecs::Ecs::getComponentMap<ecs::component::Hitbox>();
		// auto &online = ecs::Ecs::getComponentMap<ecs::component::OnlineComponent>();

		// json::Entity	data(json::Entity::ARR);
		// for (auto &elem: online) {
		// 	auto id = elem.first;
		// 	data.push(json::makeObject {
		// 		{ "id", online[id].onlineId },
		// 		{ "width", hitbox[id].width * 2 },
		// 		{ "height", hitbox[id].height * 2 },
		// 		{ "x", pos[id].x * 2 },
		// 		{ "y", pos[id].y * 2 },
		// 		{ "spriteId", (int) online[id].spriteId }
		// 	});
		// }
		// {
		// 	std::lock_guard<std::mutex>	_guard(_sheetMtx);

		// 	_sheet = data;
		// }

		end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		auto sleepTime = _sleepTime - elapsed;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime > 0 ? sleepTime : 0));
	}
	TimedEvent::get().clear();
}

void	Session::addPlayer(ClientConnection &player) {
	std::lock_guard<std::mutex>	_guard(_addPlayerMutex);


	auto cont = _players.insert(_players.end(), {&player, (ID)0});
	addTask([this, cont] () {
		auto ids = ecs::Ecs::filter<ecs::component::Position, ecs::component::Hitbox, ecs::component::OnlineComponent>();
		auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		auto &hitbox = ecs::Ecs::getComponentMap<ecs::component::Hitbox>();
		auto &online = ecs::Ecs::getComponentMap<ecs::component::OnlineComponent>();
		for (auto id: ids) {
			proto::Create	pack{
				proto::Type::CREATE, _id, 0, id,
				hitbox[id].width * 2, hitbox[id].height * 2,
				pos[id].x, pos[id].y,
				online[id].spriteId
			};

			sendToPlayer(cont->player, reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
		}

		ID id = ecs::entity::Entity::getId();

		proto::SpriteId	spriteId;
		switch (_players.size() % 4) {
			case 0: spriteId = proto::SpriteId::PLAYER1; break;
			case 1: spriteId = proto::SpriteId::PLAYER2; break;
			case 2: spriteId = proto::SpriteId::PLAYER3; break;
			case 3: spriteId = proto::SpriteId::PLAYER4; break;
		}

		proto::Create	pack{proto::Type::CREATE, _id, 0, id, 64, 32, 150, 720 / 2, spriteId};

		TimedEventAdmin t;
		ecs::Ecs::addComponent<ecs::component::Position>(id, pack.x(), pack.y());
		ecs::Ecs::addComponent<ecs::component::Speed>(id);
		ecs::Ecs::addComponent<game::Firerate>(id, 200);
		ecs::Ecs::addComponent<game::component::Type>(id, game::component::Type::Types::SHIP);

		float w = pack.w();
		float h = pack.h();
		t.addEvent(1, Time::Seconds, [id, w, h]{ 
			ecs::Ecs::addComponent<ecs::component::Hitbox>(id, w, h, true);
		});

		ecs::Ecs::addComponent<ecs::component::OnlineComponent>(id, id, pack.spriteID);
		ecs::Ecs::addComponent<ecs::component::Keyboard>(id);
		ecs::Ecs::addComponent<game::component::Inventory>(id);
		ecs::Ecs::addComponent<ecs::component::DeplacementKeyBoard>(id);
		ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[id].keyMap[KeyKeyboard::SPACE] =
			std::pair<bool, std::function<void(ID)>>(false, [this](ID id) {
				if (ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[id].keyMap[KeyKeyboard::SPACE].first)
					game::system::Fire::shoot(id, *this);
			});

		cont->ecsId = id;

		sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));

		return std::shared_ptr<proto::PacketBase>(nullptr);
	});
}

void	Session::_rmPlayer(decltype(_players)::iterator player) {
	player->isDeleted = true;
	addTask([this, player] () {
		std::lock_guard<std::mutex>	_guard(_addPlayerMutex);
		auto	ecsId = player->ecsId;

		ecs::Ecs::deleteLater(ecsId);
		_players.erase(player);

		proto::Delete	pack{proto::Type::DELETE, _id, 0, ecsId};
		sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));

		return std::shared_ptr<proto::PacketBase>(nullptr);
	});
}

void	Session::addTask(decltype(_pool)::value_type const &task) {
	std::lock_guard<std::mutex>	_guard(_pickLock);

	_pool.push_back(task);
}

void	Session::sendCreate(ID id) {
	auto ids = ecs::Ecs::filter<ecs::component::Position, ecs::component::Hitbox, ecs::component::OnlineComponent>();
	auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
	auto &hitbox = ecs::Ecs::getComponentMap<ecs::component::Hitbox>();
	auto &online = ecs::Ecs::getComponentMap<ecs::component::OnlineComponent>();

	proto::Create	pack{
		proto::Type::CREATE, _id, 0, id,
		hitbox[id].width * 2, hitbox[id].height * 2,
		pos[id].x, pos[id].y,
		online[id].spriteId
	};
	sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
}

}}