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
			std::cout << "send press Z" << std::endl;
			proto::KeyPress	buf{proto::Type::KEYPRESS, srv._sessionId, srv._id, (uint8_t) KEY };
			nw::UdpBuffer 	wbuf{reinterpret_cast<char*>(&buf), sizeof(buf)};
			srv._udpSock.sendTo(wbuf, srv._serverEp);
			key = true;
		} else if (!ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[id].keyMap[KEY].first && key) {
			std::cout << "send release Z" << std::endl;
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

	auto createRes = srv.makeSession("session1", 8);
	if (createRes["status"] == false) {
		rtype::MsgBox::show("Session create failed", "(!) " + createRes["error"]["message"].to<std::string>());
	}

	{
		rtype::Selection selection;

		selection.run(srv);
	}


	/*std::srand(std::time(nullptr));
	auto &rtype = ecs::graphical::Graphic::get();
	ecs::DataBank<std::string, sf::SoundBuffer>::get().creator = [](std::string path){
		sf::SoundBuffer buffer;
		buffer.loadFromFile(path);
		return buffer;
	};
	ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get().creator = [](std::string path){
		ecs::graphical::BundleSprite buffer;
		buffer.texture = new sf::Texture();
		buffer.texture->loadFromFile(path);
		buffer.sprite = new sf::Sprite(*buffer.texture);
		return buffer;
	};

	ID limitTop = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(limitTop, 1280/2, 0);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitTop, 1280.f, 1.f, true);
	ID limitBottom = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(limitBottom, 1280/2, 720);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitBottom, 1280.f, 1.f, true);
	ID limitLeft = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(limitLeft, 0, 720/2);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitLeft, 1.f, 720.f, true);
	ID limitRight = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(limitRight, 1280, 720/2);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitRight, 1.f, 720.f, true);

	game::system::gen Gen;
	game::system::walls Walls;

	

	ID ship = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Firerate>(ship, 100);
	ecs::Ecs::addComponent<ecs::component::Position>(ship, 1280/2, 720/2);
	ecs::Ecs::addComponent<ecs::component::Speed>(ship);
	ecs::Ecs::addComponent<game::component::Inventory>(ship);
	ecs::Ecs::addComponent<game::component::Type>(ship, game::component::Type::Types::SHIP);
	ecs::Ecs::addComponent<ecs::component::Drawable>(ship, 0, true);
	ecs::Ecs::addComponent<ecs::component::DeplacementKeyBoard>(ship, 500.f);
	ecs::Ecs::addComponent<ecs::component::Sprite>(ship, "assets/Sprite/Ship/BlueShip/BlueShip3.png", ecs::core::Vector2<float>(64, 32));
	ecs::Ecs::addComponent<ecs::component::Hitbox>(ship, ship, true, false);
	ecs::Ecs::addComponent<ecs::component::Keyboard>(ship);

	auto &keymap = ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[ship].keyMap;
	keymap[KeyKeyboard::ESCAPE] = std::pair<bool, std::function<void(ID)>>(false, [&rtype](ID parent) {rtype._window->close();});
	keymap[KeyKeyboard::SPACE] = std::pair<bool, std::function<void(ID)>>(false, &game::system::Fire::shoot);
	keymap[KeyKeyboard::KEY_Z] = std::pair<bool, std::function<void(ID)>>(false, [](){
		proto::KeyPress	buf{proto::Type::KEYPRESS, srv._sessionId, srv._id, (uint8_t) KeyKeyboard::KEY_Z };
		nw::UdpBuffer 	wbuf{reinterpret_cast<char*>(&buf), sizeof(buf)};

		srv._udpSock.sendTo(wbuf, srv._serverEp);
	});


	game.addUpdate(10, &ecs::system::Speeds::UpdateSpeeds);
	game.addUpdate(9, &game::system::ai::updateAi);
	game.addUpdate(8, &game::system::Bonuses::UpdateBonuses);
	game.addUpdate(8, [&Walls](){Walls.updateWalls();});
	game.addUpdate(9, [&Gen](){Gen.updateGen();});
	 */
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
	/*auto &map = ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[keyboard].keyMap;
	map[KeyKeyboard::KEY_Z] = std::pair<bool, std::function<void(ID)>>(false, [&srv](ID id){
		static bool key = false;
		if (ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[id].keyMap[KeyKeyboard::KEY_Z].first && !key) {
			std::cout << "send press Z" << std::endl;
			proto::KeyPress	buf{proto::Type::KEYPRESS, srv._sessionId, srv._id, (uint8_t) KeyKeyboard::KEY_Z };
			nw::UdpBuffer 	wbuf{reinterpret_cast<char*>(&buf), sizeof(buf)};
			srv._udpSock.sendTo(wbuf, srv._serverEp);
			key = true;
		} else if (!ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[id].keyMap[KeyKeyboard::KEY_Z].first && key) {
			std::cout << "send release Z" << std::endl;
			proto::KeyRelease	buf{proto::Type::KEYRELEASE, srv._sessionId, srv._id, (uint8_t) KeyKeyboard::KEY_Z };
			nw::UdpBuffer		wbuf{reinterpret_cast<char*>(&buf), sizeof(buf)};
			srv._udpSock.sendTo(wbuf, srv._serverEp);
			key = false;
		}
	});*/

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
					std::cout << "MOVE" << std::endl;
					_onReceiveMove(reinterpret_cast<proto::Move&>(*packet));
					break;
				case (proto::Type::CREATE):
					std::cout << "CREATE" << std::endl;
					_onReceiveCreate(reinterpret_cast<proto::Create&>(*packet));
					break;
				case (proto::Type::DELETE):
					std::cout << "DELETE" << std::endl;
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
		if (online[id].onlineId == packet.componentId()) {
			pos[id].x = packet.x();
			pos[id].y = packet.y();
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
		if (online[id].onlineId == packet.componentId()) {
			ecs::Ecs::deleteId(id);
			break;
		}
	}
}

}