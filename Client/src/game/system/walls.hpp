//
// Created by pierre on 27/11/2018.
//

#pragma once

#include <component/physic/Position.hpp>
#include <component/physic/Speed.hpp>
#include "component/physic/Hitbox.hpp"
#include <component/graphical/Sprite.hpp>
#include <component/graphical/Drawable.hpp>
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
				{"Sprite/Walls/Wall1.png", {192, 96}},
				{"Sprite/Walls/Wall2.png", {128, 94}},
				{"Sprite/Walls/Wall3.png", {192, 64}},
				{"Sprite/Walls/Wall4.png", {384, 110}},
				{"Sprite/Walls/Wall5.png", {384, 58}},
				{"Sprite/Walls/Wall6.png", {96, 142}},
				{"Sprite/Walls/Wall7.png", {868, 16}},
				{"Sprite/Walls/Wall8.png", {128, 110}},
				{"Sprite/WallsRotate/Wall1.png", {192, 96}},
				{"Sprite/WallsRotate/Wall2.png", {128, 94}},
				{"Sprite/WallsRotate/Wall3.png", {192, 64}},
				{"Sprite/WallsRotate/Wall4.png", {384, 110}},
				{"Sprite/WallsRotate/Wall5.png", {384, 58}},
				{"Sprite/WallsRotate/Wall6.png", {96, 142}},
				{"Sprite/WallsRotate/Wall7.png", {868, 16}},
				{"Sprite/WallsRotate/Wall8.png", {128, 110}},
			};
	};
}}