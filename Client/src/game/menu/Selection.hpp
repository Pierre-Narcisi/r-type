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
#include "component/control/LazyDeplacementMouse.hpp"
#include <ecs/DataBank.hpp>
#include <component/audio/Sound.hpp>
#include <component/control/DeplacementMouse.hpp>
#include "sfml/Graphic.hpp"
#include "core/Time.hpp"
#include "../game/component/Firerate.hpp"
#include "../game/component/Parallax.hpp"
#include "../game/system/Parallaxs.hpp"
#include "TextDisplay.hpp"
#include "Json/Entity.hpp"

#pragma once

namespace rtype {

    struct room {
        std::string name;
        int id;
        int maxNbr;
        int actualNbr;
    };

    class Selection
    {
        public:
            Selection() {}
            ~Selection() {
                for (auto id: _componentsId) {
                    ecs::Ecs::deleteId(id);
                }
            }

            void    addRoom(std::string name, int id, int maxNbr, int actualNbr)
            {
                room    rm;
                rm.actualNbr = actualNbr;
                rm.id = id;
                rm.maxNbr = maxNbr;
                rm.name = name;
                _rooms.push_back(rm);
            }

            void    run(ServerConnection &srv) {
                bool    continue_ = true;
                auto    &game = ecs::Ecs::get();
                auto    &rtype = ecs::graphical::Graphic::get();

                auto sessions = srv.getSessions();
                if (sessions["status"] == false) {
                    return;
                }
                for (auto &session: sessions["sessions"].value<json::Array>()) {
                    addRoom(
                        session["name"].to<std::string>(),
                        session["id"].to<int>(),
                        session["playerMax"].to<int>(),
                        session["playerCount"].to<int>()
                    );
                }

                ID background = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<game::Parallax>(background, "assets/space.png", 100.f);

                ID text = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(text, 1280/2, 100);
                ecs::Ecs::addComponent<ecs::component::Drawable>(text, 0, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(text, "assets/PressStart.ttf", "PLEASE CHOOSE A ROOM", 1280/2, 100);

                ID buttonPlay = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(buttonPlay, 1280/2, 640);
                ecs::Ecs::addComponent<ecs::component::Speed>(buttonPlay);
                ecs::Ecs::addComponent<ecs::component::Drawable>(buttonPlay, 0, true);
                ecs::Ecs::addComponent<ecs::component::Sprite>(buttonPlay, "assets/css-buttons.png");
                ecs::Ecs::addComponent<ecs::component::Hitbox>(buttonPlay, buttonPlay, false, [this, &continue_, &srv](ID self, ID other) {
			if (ecs::Ecs::idHasComponents<ecs::component::Mouse>(other) && ecs::Ecs::getComponentMap<ecs::component::Mouse>()[other].mouseMap[KeyMouse::LCLICK].first) {
				auto res = srv.joinSession(this->_rooms[this->_index].id);

				if (res["status"] == true) {
					continue_ = false;
				} else {
					rtype::MsgBox::show("Session create failed", "(!) " + res["error"]["message"].to<std::string>());
					continue_ = false; // RM THIS SHIT LATER
				}
			}
                });

                ID buttonNext = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<game::Firerate>(buttonNext, 100);
                ecs::Ecs::addComponent<ecs::component::Position>(buttonNext, 1280 - 1280/4, 720/2);
                ecs::Ecs::addComponent<ecs::component::Speed>(buttonNext);
                ecs::Ecs::addComponent<ecs::component::Drawable>(buttonNext, 0, true);
                ecs::Ecs::addComponent<ecs::component::Sprite>(buttonNext, "assets/ButtonNext.png");
                ecs::Ecs::addComponent<ecs::component::Hitbox>(buttonNext, buttonNext, false, [this, &continue_](ID parent, ID other){
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire).count() > ecs::Ecs::getComponentMap<game::Firerate>()[parent]._firerate)
                    {
                        if (ecs::Ecs::idHasComponents<ecs::component::Mouse>(other) && ecs::Ecs::getComponentMap<ecs::component::Mouse>()[other].mouseMap[KeyMouse::LCLICK].first)
                        {
                            this->_index += 1;
                            if (_index > _rooms.size() - 1)
                                this->_index = 0;
                        }
                        ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire = std::chrono::system_clock::now();
                    }
                });

                ID buttonPrev = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(buttonPrev, 1280/4, 720/2);
                ecs::Ecs::addComponent<ecs::component::Speed>(buttonPrev);
                ecs::Ecs::addComponent<ecs::component::Drawable>(buttonPrev, 0, true);
                ecs::Ecs::addComponent<ecs::component::Sprite>(buttonPrev, "assets/ButtonPrev.png");
                ecs::Ecs::addComponent<ecs::component::Hitbox>(buttonPrev, buttonPrev, false, [this, &continue_](ID parent, ID other){
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire).count() > ecs::Ecs::getComponentMap<game::Firerate>()[parent]._firerate)
                    {
                        if (ecs::Ecs::idHasComponents<ecs::component::Mouse>(other) && ecs::Ecs::getComponentMap<ecs::component::Mouse>()[other].mouseMap[KeyMouse::LCLICK].first)
                        {
                            this->_index -= 1;
                            if (_index < 0)
                                this->_index = _rooms.size();
                        }
                        ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire = std::chrono::system_clock::now();
                    }
                });

                ID name = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(name, 1280/2, 300);
                ecs::Ecs::addComponent<ecs::component::Drawable>(name, 10, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(name, "assets/PressStart.ttf", "NAME", 1280/2, 230, false, sf::Color::Red, 30);

                ID txt_current_nbr = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(txt_current_nbr, 1280/2, 720/2 - 60);
                ecs::Ecs::addComponent<ecs::component::Drawable>(txt_current_nbr, 10, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(txt_current_nbr, "assets/PressStart.ttf", "Current player :", 1280/2, 720/2 - 60, false, sf::Color::Red, 25);

                ID actual_nbr = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(actual_nbr, 1280/2, 720/2 - 30);
                ecs::Ecs::addComponent<ecs::component::Drawable>(actual_nbr, 10, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(actual_nbr, "assets/PressStart.ttf", "1", 1280/2, 720/2 - 30, false, sf::Color::Red, 25);

                ID txt_max_nbr = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(txt_max_nbr, 1280/2, 720/2 + 30);
                ecs::Ecs::addComponent<ecs::component::Drawable>(txt_max_nbr, 10, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(txt_max_nbr, "assets/PressStart.ttf", "Max player :", 1280/2, 720/2 + 30, false, sf::Color::Red, 25);

                ID max_nbr = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(max_nbr, 1280/2, 720/2 + 60);
                ecs::Ecs::addComponent<ecs::component::Drawable>(max_nbr, 10, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(max_nbr, "assets/PressStart.ttf", "4", 1280/2, 720/2 + 60, false, sf::Color::Red, 25);

                ID back = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(back, 1280/2, 720/2);
                ecs::Ecs::addComponent<ecs::component::Speed>(back);
                ecs::Ecs::addComponent<ecs::component::Drawable>(back, 0, true);
                ecs::Ecs::addComponent<ecs::component::Sprite>(back, "assets/Back.png");

                ID mouse = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(mouse);
                ecs::Ecs::addComponent<ecs::component::Speed>(mouse);
                ecs::Ecs::addComponent<ecs::component::Mouse>(mouse);
                ecs::Ecs::getComponentMap<ecs::component::Mouse>()[mouse].mouseMap[KeyMouse::LCLICK];
                ecs::Ecs::addComponent<ecs::component::LazyDeplacementMouse>(mouse);
                ecs::Ecs::addComponent<ecs::component::Hitbox>(mouse, 10.f, 10.f);

                _componentsId = { background, buttonPlay, mouse, text, back, max_nbr, actual_nbr, txt_current_nbr, txt_max_nbr, name, buttonPrev, buttonNext };


                game.addUpdate(100, [this, name, actual_nbr, max_nbr](){
                    if (_rooms.size() > 0){
                        auto ids = ecs::Ecs::filter<ecs::component::TextDisplay>();
                        auto &txt = ecs::Ecs::getComponentMap<ecs::component::TextDisplay>();

                        for (auto id : ids) {
                            if (id == name){
                                txt[id]._str = _rooms[_index].name;
                            }
                            if (id == actual_nbr)
                            {
                                txt[id]._str = std::to_string(_rooms[_index].actualNbr);
                            }
                            if (id == max_nbr)
                            {
                                txt[id]._str = std::to_string(_rooms[_index].maxNbr);
                            }
                        }
                    }
                });
                ecs::Ecs::addComponent<ecs::component::Drawable>(back, 0, true);

                game.addUpdate(100, [&rtype](){ rtype.update(); });
                game.addUpdate(1, &game::Parallaxs::UpdateParallaxs);
                // /game.addUpdate(1, ecs::component::UpdateTextDisplay);
                game.addUpdate(10, &ecs::system::Controls::UpdateDeplacement);
                game.addUpdate(10, &ecs::system::Speeds::UpdateSpeeds);
		game.addUpdate(2, &ecs::system::Controls::UpdateKeyboards);
		game.addUpdate(2, &ecs::system::Controls::UpdateMouses);

                while (continue_ && ecs::graphical::Graphic::get().isOpen()) {
                    long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
                    ecs::Ecs::get().update();

                    auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);
                    std::this_thread::sleep_for(std::chrono::microseconds(x));
                }
                std::cout << "clear ids" << std::endl;
                game.clearUpdates();
		std::cout << "clear ids done" << std::endl;
            }

        private:
            int                 _index = 0;
            std::vector<room>    _rooms;
            std::vector<ID>     _componentsId;
    };
}