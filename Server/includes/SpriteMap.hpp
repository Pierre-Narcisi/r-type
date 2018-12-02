/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** SpriteMap.hpp
*/

#if !defined(_SPRITE_MAP_HPP)
#define _SPRITE_MAP_HPP

#include <unordered_map>
#include "Network/GameProtocol.hpp"

namespace rtype {

static std::unordered_map<proto::SpriteId, std::string>	Sprites = {
	{ proto::SpriteId::PLAYER1, "assets/Sprite/Ship/BlueShip/BlueShip3.png" },
	{ proto::SpriteId::PLAYER2, "assets/Sprite/Ship/GreenShip/GreenShip3.png" },
	{ proto::SpriteId::PLAYER3, "assets/Sprite/Ship/PurpleShip/PurpleShip3.png" },
	{ proto::SpriteId::PLAYER4, "assets/Sprite/Ship/RedShip/RedShip3.png" },

	{ proto::SpriteId::BACKGROUND, "assets/space.png" },

	{ proto::SpriteId::WALL1, "assets/Sprite/Walls/Wall1.png" },
	{ proto::SpriteId::WALL2, "assets/Sprite/Walls/Wall2.png" },
	{ proto::SpriteId::WALL3, "assets/Sprite/Walls/Wall3.png" },
	{ proto::SpriteId::WALL4, "assets/Sprite/Walls/Wall4.png" },
	{ proto::SpriteId::WALL5, "assets/Sprite/Walls/Wall5.png" },
	{ proto::SpriteId::WALL6, "assets/Sprite/Walls/Wall6.png" },
	{ proto::SpriteId::WALL7, "assets/Sprite/Walls/Wall7.png" },
	{ proto::SpriteId::WALL8, "assets/Sprite/Walls/Wall8.png" },
	{ proto::SpriteId::WALL_ROTATE1, "assets/Sprite/WallsRotate/Wall1.png" },
	{ proto::SpriteId::WALL_ROTATE2, "assets/Sprite/WallsRotate/Wall2.png" },
	{ proto::SpriteId::WALL_ROTATE3, "assets/Sprite/WallsRotate/Wall3.png" },
	{ proto::SpriteId::WALL_ROTATE4, "assets/Sprite/WallsRotate/Wall4.png" },
	{ proto::SpriteId::WALL_ROTATE5, "assets/Sprite/WallsRotate/Wall5.png" },
	{ proto::SpriteId::WALL_ROTATE6, "assets/Sprite/WallsRotate/Wall6.png" },
	{ proto::SpriteId::WALL_ROTATE7, "assets/Sprite/WallsRotate/Wall7.png" },
	{ proto::SpriteId::WALL_ROTATE8, "assets/Sprite/WallsRotate/Wall8.png" },

	{ proto::SpriteId::BONUS, "assets/Sprite/Bonuses/bonuses1.png" },

	{ proto::SpriteId::EXPLOSION, "assets/Sprite/Explosion" },
	{ proto::SpriteId::BIG_EXPLOSION, "assets/Sprite/BigExplosion" },

	{ proto::SpriteId::BULLET1, "assets/Sprite/ClassicBullet/ClassicBullet1.png" },
	{ proto::SpriteId::BULLET2, "assets/Sprite/ClassicBullet/ClassicBullet2.png" },
	{ proto::SpriteId::BULLET3, "assets/Sprite/ClassicBullet/ClassicBullet3.png" },

	{ proto::SpriteId::ENEMY1, "assets/Sprite/Enemy1" },
	{ proto::SpriteId::ENEMY2, "assets/Sprite/Enemy2/Enemy2walk" },
	{ proto::SpriteId::ENEMY3, "assets/Sprite/Enemy3" }
};

}

#endif // _SPRITE_MAP_HPP
