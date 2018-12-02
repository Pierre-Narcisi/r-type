/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Game.cpp
*/

#include <boost/filesystem.hpp>
#include "Game.hpp"
#include "ecs/Ecs.hpp"
#include "src/game/menu/Menu.hpp"
#include "system/control/Controls.hpp"
#include "component/online/OnlineComponent.hpp"
#include "game/menu/Selection.hpp"
#include "SpriteMap.hpp"
#include "Game.hpp"

namespace rtype {

template <KeyKeyboard KEY>
void 	Game::_keyboardFactory(ID keyboard, ServerConnection &srv) {
	auto &map = ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[keyboard].keyMap;

	map[KEY] = std::pair<bool, std::function<void(ID)>>(false, [&srv](ID id){
		static bool key = false;
		if (ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[id].keyMap[KEY].first && !key) {
			//std::cout << "send press Z" << std::endl;
			proto::KeyPress	buf{proto::Type::KEYPRESS, srv._sessionId, srv._id, (uint8_t) KEY };
			nw::UdpBuffer 	wbuf{reinterpret_cast<char*>(&buf), sizeof(buf)};
			srv._udpSock.sendTo(wbuf, srv._serverEp);
			key = true;
		} else if (!ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[id].keyMap[KEY].first && key) {
			//std::cout << "send release Z" << std::endl;
			proto::KeyRelease	buf{proto::Type::KEYRELEASE, srv._sessionId, srv._id, (uint8_t) KEY };
			nw::UdpBuffer		wbuf{reinterpret_cast<char*>(&buf), sizeof(buf)};
			srv._udpSock.sendTo(wbuf, srv._serverEp);
			key = false;
		}
	});
}

void	Game::start(ServerConnection &srv) {
	{
		rtype::Menu menu;

		menu.run(srv);
	}

	{
		rtype::Selection selection;

		selection.run(srv);
	}

	auto &game = ecs::Ecs::get();

	ID background = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Parallax>(background, Sprites[proto::SpriteId::BACKGROUND], 100.f);

	auto &rtype = ecs::graphical::Graphic::get();
	game.addUpdate(100, [&rtype](){rtype.update();});
	game.addUpdate(1, &game::Parallaxs::UpdateParallaxs);
	game.addUpdate(10, &ecs::system::Controls::UpdateDeplacement);
	game.addUpdate(2, &ecs::system::Controls::UpdateKeyboards);
	game.addUpdate(2, &ecs::system::Controls::UpdateMouses);

	ID keyboard = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Keyboard>(keyboard);

	_keyboardFactory<KeyKeyboard::KEY_Z>(keyboard, srv);
	_keyboardFactory<KeyKeyboard::KEY_Q>(keyboard, srv);
	_keyboardFactory<KeyKeyboard::KEY_S>(keyboard, srv);
	_keyboardFactory<KeyKeyboard::KEY_D>(keyboard, srv);
	_keyboardFactory<KeyKeyboard::SPACE>(keyboard, srv);

	while (rtype.isOpen()) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		auto list = srv.getAvailablePackets();

		for (auto &packet: list) {
			switch (packet->type) {
				case (proto::Type::MOVE):
					//std::cout << "MOVE" << std::endl;
					_onReceiveMove(reinterpret_cast<proto::Move&>(*packet));
					break;
				case (proto::Type::CREATE):
					//std::cout << "CREATE" << std::endl;
					_onReceiveCreate(reinterpret_cast<proto::Create&>(*packet));
					break;
				case (proto::Type::DELETE):
					//std::cout << "DELETE" << std::endl;
					_onReceiveDelete(reinterpret_cast<proto::Delete&>(*packet));
					break;
				default: break;
			}
		}

		game.update();

		auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(x));
	}
}

void	Game::_onReceiveMove(proto::Move &packet) {
	auto ids = ecs::Ecs::filter<ecs::component::Position, ecs::component::OnlineComponent>();
	auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
	auto &online = ecs::Ecs::getComponentMap<ecs::component::OnlineComponent>();

	for (auto id : ids) {
		if (online[id].onlineId == (ID)packet.componentId()) {
			pos[id].x = (float)packet.x();
			pos[id].y = (float)packet.y();
			break;
		}
	}
}

void	Game::_onReceiveCreate(proto::Create &packet) {
	ID id = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Drawable>(id, 3, true);
	ecs::Ecs::addComponent<ecs::component::Position>(id, packet.x(), packet.y());
	ecs::Ecs::addComponent<ecs::component::OnlineComponent>(id, packet.componentId(), packet.spriteID);
	
	auto &path = rtype::Sprites[packet.spriteID];
	if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path))
		ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(
			id,
			path,
			8,
			ecs::core::Vector2<float> { (float) packet.w(), (float) packet.h() }
		);
	else
		ecs::Ecs::addComponent<ecs::component::Sprite>(
			id,
			path,
			ecs::core::Vector2<float> { (float) packet.w(), (float) packet.h() }
		);
}

void	Game::_onReceiveDelete(proto::Delete &packet) {
	auto ids = ecs::Ecs::filter<ecs::component::OnlineComponent>();
	auto &online = ecs::Ecs::getComponentMap<ecs::component::OnlineComponent>();

	for (auto id : ids) {
		if (online[id].onlineId == (ID)packet.componentId()) {
			ecs::Ecs::deleteId(id);
			break;
		}
	}
}

}