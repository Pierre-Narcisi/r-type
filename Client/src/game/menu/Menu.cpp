
#include "component/ai.hpp"
#include "system/gen.hpp"
#include "enemy/enemy1/enemy1.hpp"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "system/ai.hpp"
#include <zconf.h>
#include <ecs/Entity.hpp>
#include <ecs/Ecs.hpp>
#include <component/graphical/Sprite.hpp>
#include <system/graphical/Graphicals.hpp>
#include <component/physic/Position.hpp>
#include <component/control/DeplacementKeyBoard.hpp>
#include <component/control/Keyboard.hpp>
#include <component/physic/Speed.hpp>
#include <system/physic/Speeds.hpp>
#include <component/physic/Hitbox.hpp>
#include <component/graphical/AnimatedSprite.hpp>
#include <component/graphical/AnimatedSpriteMap.hpp>
#include <component/graphical/Drawable.hpp>
#include <ecs/DataBank.hpp>
#include <component/audio/Sound.hpp>
#include <component/control/DeplacementMouse.hpp>
#include "sfml/Graphic.hpp"
#include "core/Time.hpp"
#include "../lib/TimedEvent/TimedEventAdmin.hpp"
#include "game/component/Parallax.hpp"
#include "game/component/Firerate.hpp"
#include "game/component/AnimationRtype.hpp"
#include "game/system/Parallaxs.hpp"

void    menu()
{

    std::srand(std::time(nullptr));
    auto &rtype = ecs::graphical::Graphic::get();

    ID background = ecs::entity::Entity::getId();
    ecs::Ecs::addComponent<ecs::component::Position>(background, 1280/2, 720/2);
    ecs::Ecs::addComponent<ecs::component::Drawable>(background, 0, true);
    ecs::Ecs::addComponent<ecs::component::Sprite>(background, "Sprite/Ship/space.png");

    ID Titre = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(Titre, 1280/2, 720/2);
    ecs::Ecs::addComponent<ecs::component::Drawable>(Titre, 0, true);
    ecs::Ecs::addComponent<ecs::component::Sprite>(Titre, "Sprite/Ship/r_type_logo.png");




    // ID ButtonPlay = ecs::entity::Entity::getId();
    // ecs::Ecs::addComponent<ecs::component::Position>(ButtonPlay, 1280/2, 0);
	// ecs::Ecs::addComponent<ecs::component::Hitbox>(limitTop, 1280, 1, true);


    ID ship = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Firerate>(ship, 100);
	ecs::Ecs::addComponent<ecs::component::Position>(ship, 1280/2, 720/2);
	ecs::Ecs::addComponent<ecs::component::Speed>(ship);
	ecs::Ecs::addComponent<ecs::component::Drawable>(ship, 0, true);
	ecs::Ecs::addComponent<ecs::component::DeplacementKeyBoard>(ship, 300.f);
	ecs::Ecs::addComponent<ecs::component::Sprite>(ship, "Sprite/Ship/BlueShip/BlueShip3.png");
	ecs::Ecs::addComponent<ecs::component::Hitbox>(ship, ecs::graphical::Graphic::getTextureSize("Sprite/Ship/BlueShip/up/BlueShip1.png").x, ecs::graphical::Graphic::getTextureSize("Sprite/Ship/BlueShip/up/BlueShip1.png").y, true);

    auto &game = ecs::Ecs::get();

    while (rtype.isOpen()) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		game.update();
	
		auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(x));
	}
}