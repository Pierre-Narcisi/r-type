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

            void    run() {
                bool    continue_ = true;
                auto    &game = ecs::Ecs::get();
                auto    &rtype = ecs::graphical::Graphic::get();

                addRoom("salut", 1, 4, 2);
                addRoom("salut2", 2, 4, 1);

                

                ID background = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<game::Parallax>(background, "assets/space.png", 100.f);

                ID text = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(text, 1280/2, 100);
                ecs::Ecs::addComponent<ecs::component::Drawable>(text, 0, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(text, "assets/PressStart.ttf", "PLEASE CHOOSE A WAY TO JOIN A ROOM", 1280/2, 100);

                ID buttonNext = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<game::Firerate>(buttonNext, 100);
                ecs::Ecs::addComponent<ecs::component::Position>(buttonNext, 1280/2 - 50, 720/2);
                ecs::Ecs::addComponent<ecs::component::Speed>(buttonNext);
                ecs::Ecs::addComponent<ecs::component::Drawable>(buttonNext, 0, true);
                ecs::Ecs::addComponent<ecs::component::Sprite>(buttonNext, "assets/ButtonNext.png");
                ecs::Ecs::addComponent<ecs::component::Hitbox>(buttonNext, buttonNext, false, [&continue_, this](ID parent, ID other){
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
                ecs::Ecs::addComponent<game::Firerate>(buttonPrev, 100);
                ecs::Ecs::addComponent<ecs::component::Position>(buttonPrev, 50, 720/2);
                ecs::Ecs::addComponent<ecs::component::Speed>(buttonPrev);
                ecs::Ecs::addComponent<ecs::component::Drawable>(buttonPrev, 0, true);
                ecs::Ecs::addComponent<ecs::component::Sprite>(buttonPrev, "assets/ButtonPrev.png");
                ecs::Ecs::addComponent<ecs::component::Hitbox>(buttonPrev, buttonPrev, false, [&continue_, this](ID parent, ID other){
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire).count() > ecs::Ecs::getComponentMap<game::Firerate>()[parent]._firerate)
                    {
                        if (ecs::Ecs::idHasComponents<ecs::component::Mouse>(other) && ecs::Ecs::getComponentMap<ecs::component::Mouse>()[other].mouseMap[KeyMouse::LCLICK].first)
                        {
                            this->_index -= 1;
                            if (_index < 0)
                                this->_index = _rooms.size() - 1;
                        }
                        ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire = std::chrono::system_clock::now();
                    }
                });

                ID txtCreation = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(txtCreation, 1280/2 + 1280/4, 250);
                ecs::Ecs::addComponent<ecs::component::Speed>(txtCreation);
                ecs::Ecs::addComponent<ecs::component::Drawable>(txtCreation, 0, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(txtCreation, "assets/PressStart.ttf", "ENTER THE NAME OF\n\n YOUR NEW ROOM", 1280/2 + 1280/4, 250);

                ID inputCreation = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(inputCreation, 1280/2 + 1280/4, 720/2);
                ecs::Ecs::addComponent<ecs::component::Speed>(inputCreation);
                ecs::Ecs::addComponent<ecs::component::Drawable>(inputCreation, 0, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(inputCreation, "assets/PressStart.ttf", "", 1280/2 + 1280/4, 720/2, true);

                ID name = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(name, 1280/4, 300);
                ecs::Ecs::addComponent<ecs::component::Drawable>(name, 10, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(name, "assets/PressStart.ttf", "NAME", 1280/4, 230, false, sf::Color::Red, 30);

                ID txt_current_nbr = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(txt_current_nbr, 1280/4, 720/2 - 60);
                ecs::Ecs::addComponent<ecs::component::Drawable>(txt_current_nbr, 10, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(txt_current_nbr, "assets/PressStart.ttf", "Current player :", 1280/4, 720/2 - 60, false, sf::Color::Red, 25);

                ID actual_nbr = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(actual_nbr, 1280/4, 720/2 - 30);
                ecs::Ecs::addComponent<ecs::component::Drawable>(actual_nbr, 10, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(actual_nbr, "assets/PressStart.ttf", "1", 1280/4, 720/2 - 30, false, sf::Color::Red, 25);

                ID txt_max_nbr = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(txt_max_nbr, 1280/4, 720/2 + 30);
                ecs::Ecs::addComponent<ecs::component::Drawable>(txt_max_nbr, 10, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(txt_max_nbr, "assets/PressStart.ttf", "Max player :", 1280/4, 720/2 + 30, false, sf::Color::Red, 25);

                ID max_nbr = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(max_nbr, 1280/4, 720/2 + 60);
                ecs::Ecs::addComponent<ecs::component::Drawable>(max_nbr, 10, true);
                ecs::Ecs::addComponent<ecs::component::TextDisplay>(max_nbr, "assets/PressStart.ttf", "4", 1280/4, 720/2 + 60, false, sf::Color::Red, 25);

                ID back = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(back, 1280/4, 720/2);
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

                ID key = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Keyboard>(key);

                ID buttonJoin = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(buttonJoin, 1280/4, 640);
                ecs::Ecs::addComponent<ecs::component::Speed>(buttonJoin);
                ecs::Ecs::addComponent<ecs::component::Drawable>(buttonJoin, 0, true);
                ecs::Ecs::addComponent<ecs::component::Sprite>(buttonJoin, "assets/css-buttons.png");
                ecs::Ecs::addComponent<ecs::component::Hitbox>(buttonJoin, buttonJoin, false, [&continue_](ID self, ID other){
                    if (ecs::Ecs::idHasComponents<ecs::component::Mouse>(other) && ecs::Ecs::getComponentMap<ecs::component::Mouse>()[other].mouseMap[KeyMouse::LCLICK].first)
                        continue_ = false;
                });

                ID buttonCreate = ecs::entity::Entity::getId();
                ecs::Ecs::addComponent<ecs::component::Position>(buttonCreate, 1280 - 1280/ 4, 500);
                ecs::Ecs::addComponent<ecs::component::Speed>(buttonCreate);
                ecs::Ecs::addComponent<ecs::component::Drawable>(buttonCreate, 0, true);
                ecs::Ecs::addComponent<ecs::component::Sprite>(buttonCreate, "assets/css-buttons.png");
                ecs::Ecs::addComponent<ecs::component::Hitbox>(buttonCreate, buttonCreate, false, [&continue_](ID self, ID other){
                    if (ecs::Ecs::idHasComponents<ecs::component::Mouse>(other) && ecs::Ecs::getComponentMap<ecs::component::Mouse>()[other].mouseMap[KeyMouse::LCLICK].first)
                        continue_ = false;
                });

                _componentsId = { background, buttonJoin, mouse, text, back, max_nbr, actual_nbr, txt_current_nbr, txt_max_nbr, name, buttonPrev, buttonNext, buttonCreate, buttonJoin, inputCreation, txtCreation };


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

                while (continue_ && ecs::graphical::Graphic::get().isOpen()) {
                    long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
                    ecs::Ecs::get().update();

                    auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);
                    std::this_thread::sleep_for(std::chrono::microseconds(x));
                }
                game.clearUpdates();
            }

        private:
            int                 _index = 0;
            std::vector<room>    _rooms;
            std::vector<ID>     _componentsId;
    };
}