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
#include "../game/component/Parallax.hpp"
#include "../game/system/Parallaxs.hpp"
#include "TextDisplay.hpp"
#include "ServerConnection.hpp"
#include "MessageBox.hpp"

#pragma once

namespace rtype {

class Menu
{
    public:
        Menu() {}
        ~Menu() {
            for (auto id: componentsId) {
                ecs::Ecs::deleteId(id);
            }
        };

        static void    tryToConnect(bool &continue_, ServerConnection &srv, ID input) {
            if (!continue_)
                return;
            auto name = ecs::Ecs::getComponentMap<ecs::component::TextDisplay>()[input]._str;
            auto loginRes = srv.login(name);
            std::cout << loginRes << std::endl;
            if (loginRes["status"] == false) {
                rtype::MsgBox::show("Login failed", "(!) " + loginRes["error"]["message"].to<std::string>());
            } else {
                continue_ = false;
            }
        }

        void    run(ServerConnection &srv) {
            bool    continue_ = true;
            auto    &game = ecs::Ecs::get();
            auto    &rtype = ecs::graphical::Graphic::get();
            

            ID background = ecs::entity::Entity::getId();
	        ecs::Ecs::addComponent<game::Parallax>(background, "assets/space.png", 100.f);

            ID title = ecs::entity::Entity::getId();
	        ecs::Ecs::addComponent<ecs::component::Position>(title, 1280/2, 720/4);
            ecs::Ecs::addComponent<ecs::component::Drawable>(title, 0, true);
            ecs::Ecs::addComponent<ecs::component::Sprite>(title, "assets/r_type_logo.png");

            ID text = ecs::entity::Entity::getId();
            ecs::Ecs::addComponent<ecs::component::Position>(text, 1280/2, 360);
            ecs::Ecs::addComponent<ecs::component::Drawable>(text, 0, true);
            ecs::Ecs::addComponent<ecs::component::TextDisplay>(text, "assets/PressStart.ttf", "PLEASE ENTER YOUR LOGIN", 1280/2, 360);

            ID input = ecs::entity::Entity::getId();
            ecs::Ecs::addComponent<ecs::component::Position>(input, 1280/2, 420);
            ecs::Ecs::addComponent<ecs::component::Drawable>(input, 0, true);
            ecs::Ecs::addComponent<ecs::component::TextDisplay>(input, "assets/PressStart.ttf", "", 1280/2, 420, true);
            //ecs::Ecs::addComponent<ecs::component::Keyboard>(input);

            ID buttonPlay = ecs::entity::Entity::getId();
            ecs::Ecs::addComponent<ecs::component::Position>(buttonPlay, 1280/2, 600);
            ecs::Ecs::addComponent<ecs::component::Speed>(buttonPlay);
            ecs::Ecs::addComponent<ecs::component::Drawable>(buttonPlay, 0, true);
            ecs::Ecs::addComponent<ecs::component::Sprite>(buttonPlay, "assets/css-buttons.png");
            ecs::Ecs::addComponent<ecs::component::Hitbox>(buttonPlay, buttonPlay, false, [&continue_, &srv, input](ID self, ID other){
                if (ecs::Ecs::idHasComponents<ecs::component::Mouse>(other) && ecs::Ecs::getComponentMap<ecs::component::Mouse>()[other].mouseMap[KeyMouse::LCLICK].first)
                    Menu::tryToConnect(continue_, srv, input);
            });

            ID mouse = ecs::entity::Entity::getId();
            ecs::Ecs::addComponent<ecs::component::Position>(mouse);
            ecs::Ecs::addComponent<ecs::component::Speed>(mouse);
            ecs::Ecs::addComponent<ecs::component::Drawable>(mouse, 3, true);
            ecs::Ecs::addComponent<ecs::component::Sprite>(mouse, "assets/Sprite/Ship/BlueShip/BlueShip3.png");
            ecs::Ecs::addComponent<ecs::component::Mouse>(mouse);
            ecs::Ecs::getComponentMap<ecs::component::Mouse>()[mouse].mouseMap[KeyMouse::LCLICK];
            ecs::Ecs::addComponent<ecs::component::DeplacementMouse>(mouse, 100000.f);
            ecs::Ecs::addComponent<ecs::component::Hitbox>(mouse, mouse, false);

            ID key = ecs::entity::Entity::getId();
            ecs::Ecs::addComponent<ecs::component::Keyboard>(key);
            ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[key].keyMap[KeyKeyboard::ENTER] =
            std::pair<bool, std::function<void(ID)>>(false, [&continue_, &srv, input] (ID parent) {
                Menu::tryToConnect(continue_, srv, input);
            });

            componentsId = { background, title, buttonPlay, mouse, input, text, key };

            game.addUpdate(100, [&rtype](){ rtype.update(); });
            game.addUpdate(1, &game::Parallaxs::UpdateParallaxs);
            //game.addUpdate(1, ecs::component::UpdateTextDisplay);
	        game.addUpdate(10, &ecs::system::Controls::UpdateDeplacement);
	        game.addUpdate(10, &ecs::system::Speeds::UpdateSpeeds);

            while (continue_ && ecs::graphical::Graphic::get().isOpen()) {
                long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
                ecs::Ecs::get().update();

                auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);
                std::this_thread::sleep_for(std::chrono::microseconds(x));
            }

            game.clearUpdates();
        }

    private:

        std::vector<ID>     componentsId;
};

}
