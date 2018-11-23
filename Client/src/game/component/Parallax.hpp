
#include "../../game_engine/component/graphical/Sprite.hpp"

namespace game {
    struct Parallax {
        Parallax() {}
        Parallax(std::string path, float speed): sprite(path) {
            this->speed = speed;
            position.x = sprite.size.x / 2;
            position.y = sprite.size.y / 2;
            sprite.sprite->setPosition(position.x, position.y);
        }

        ecs::component::Sprite      sprite;
        float                       speed;
        long                        lastTime;
        ecs::core::Vector2<float>   position;
    };
}