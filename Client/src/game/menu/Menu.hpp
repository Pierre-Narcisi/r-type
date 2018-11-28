#include <iostream>
#include <chrono>
#include <thread>
#include <ecs/Entity.hpp>
#include <ecs/Ecs.hpp>
#include <component/graphical/Sprite.hpp>
#include <system/graphical/Graphicals.hpp>
#include <component/physic/Position.hpp>
#include <component/physic/Speed.hpp>
#include <system/physic/Speeds.hpp>
#include <component/physic/Hitbox.hpp>
#include <component/graphical/Drawable.hpp>
#include <ecs/DataBank.hpp>
#include <component/audio/Sound.hpp>
#include <component/control/DeplacementMouse.hpp>
#include "sfml/Graphic.hpp"
#include "core/Time.hpp"
#include "game/component/Parallax.hpp"
#include "game/system/Parallaxs.hpp"

namespace rtype {

class Menu
{
    public:
        Menu() = default;
        ~Menu() {
            for (auto id: componentsId) {
                ecs::Ecs::deleteId(id);
            }
        };

        void    run() {
            bool    continue_ = true;

            ID background = ecs::entity::Entity::getId();
	        ecs::Ecs::addComponent<game::Parallax>(background, "assets/space.png", 100.f);

            ID title = ecs::entity::Entity::getId();
	        ecs::Ecs::addComponent<ecs::component::Position>(title, 1280/2, 720/2);
            ecs::Ecs::addComponent<ecs::component::Drawable>(title, 0, true);
            ecs::Ecs::addComponent<ecs::component::Sprite>(title, "Sprite/Ship/r_type_logo.png");

            ID buttonPlay = ecs::entity::Entity::getId();
            ecs::Ecs::addComponent<ecs::component::Position>(title, 1280/2, 500);
            ecs::Ecs::addComponent<ecs::component::Drawable>(title, 0, true);
            ecs::Ecs::addComponent<ecs::component::Sprite>(title, "Sprite/Ship/r_type_logo.png");
            ecs::Ecs::addComponent<ecs::component::Hitbox>(title, ecs::graphical::Graphic::getTextureSize("Sprite/Ship/BlueShip/up/BlueShip1.png").x, ecs::graphical::Graphic::getTextureSize("Sprite/Ship/BlueShip/up/BlueShip1.png").y, true, [&continue_](){
                continue_ = false;
            });

            componentsId = { background, title, buttonPlay };
            while (continue_) {
                long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
                ecs::Ecs::get().update();
	
                auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);
                std::this_thread::sleep_for(std::chrono::microseconds(x));
            }

        }

    private:

        std::vector<ID>     componentsId;
};

}
