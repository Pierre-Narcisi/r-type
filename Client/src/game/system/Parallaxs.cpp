#include "Parallaxs.hpp"
#include "../component/Parallax.hpp"
#include "../../game_engine/core/Time.hpp"
#include <iostream>

namespace game {
    void Parallaxs::UpdateParallaxs () {
        auto ids = ecs::Ecs::filter<Parallax>();
        auto window = ecs::graphical::Graphic::getWindow();
        auto &sprites = ecs::Ecs::getComponentMap<Parallax>();

        for (auto id : ids) {
            sprites[id].position.x = sprites[id].position.x - ((sprites[id].speed/1000000.f) * (ecs::core::Time::get(TimeUnit::MicroSeconds) - sprites[id].lastTime));
            if (sprites[id].position.x <= -static_cast<float>(sprites[id].sprite.size.x / 2))
                sprites[id].position.x = sprites[id].sprite.size.x / 2;
            sprites[id].sprite.sprite->setPosition(sprites[id].position.x, sprites[id].position.y);
            window->draw(*sprites[id].sprite.sprite);
            sprites[id].sprite.sprite->setPosition(sprites[id].position.x + sprites[id].sprite.size.x, sprites[id].position.y);
            window->draw(*sprites[id].sprite.sprite);
            sprites[id].lastTime = ecs::core::Time::get(TimeUnit::MicroSeconds);
        }
    }
}