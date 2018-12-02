//
// Created by pierre on 27/11/2018.
//

#pragma once

#include <component/physic/Position.hpp>
#include <component/physic/Speed.hpp>
#include "component/physic/Hitbox.hpp"
#include <component/graphical/Sprite.hpp>
#include <component/graphical/Drawable.hpp>
#include "component/Types.hpp"
#include <ecs/DataBank.hpp>
#include <ecs/Ecs.hpp>
#include "component/wall.hpp"


namespace game {namespace system {
	class walls {
		public:
			void updateUp();
			void updateDown();
			void updateWalls();
		private:
			ID _bindUp = -1;
			ID _bindDown = -1;
			const std::vector<std::pair<std::string, ecs::core::Vector2<float>>> _wallList = {
				{"", {0, 0}},
				{"assets/Sprite/Walls/Wall1.png", {192, 96}},
				{"assets/Sprite/Walls/Wall2.png", {128, 94}},
				{"assets/Sprite/Walls/Wall3.png", {192, 64}},
				{"assets/Sprite/Walls/Wall4.png", {384, 110}},
				{"assets/Sprite/Walls/Wall5.png", {384, 58}},
				{"assets/Sprite/Walls/Wall6.png", {96, 142}},
				{"assets/Sprite/Walls/Wall7.png", {868, 16}},
				{"assets/Sprite/Walls/Wall8.png", {128, 110}},
				{"assets/Sprite/WallsRotate/Wall1.png", {192, 96}},
				{"assets/Sprite/WallsRotate/Wall2.png", {128, 94}},
				{"assets/Sprite/WallsRotate/Wall3.png", {192, 64}},
				{"assets/Sprite/WallsRotate/Wall4.png", {384, 110}},
				{"assets/Sprite/WallsRotate/Wall5.png", {384, 58}},
				{"assets/Sprite/WallsRotate/Wall6.png", {96, 142}},
				{"assets/Sprite/WallsRotate/Wall7.png", {868, 16}},
				{"assets/Sprite/WallsRotate/Wall8.png", {128, 110}},
			};
	};
}}