//
// Created by pierre on 27/11/2018.
//

#pragma once

#define NOSPRITE

#include "component/physic/Position.hpp"
#include "component/physic/Speed.hpp"
#include "component/physic/Hitbox.hpp"
#include "Session/components/Types.hpp"
#include "ecs/DataBank.hpp"
#include "ecs/Ecs.hpp"
#include "Server/includes/Session/Session.hpp"
#include "Session/components/wall.hpp"
#include "Network/GameProtocol.hpp"

#undef NOSPRITE

namespace game {namespace system {
	class walls {
		public:
			void updateUp(rtype::session::Session &session);
			void updateDown(rtype::session::Session &session);
			void updateWalls(rtype::session::Session &session);
		private:
			ID _bindUp = -1;
			ID _bindDown = -1;
			const std::vector<std::pair<proto::SpriteId, ecs::core::Vector2<float>>> _wallList = {
				{proto::SpriteId::WALL1, {192, 96}},
				{proto::SpriteId::WALL2, {128, 94}},
				{proto::SpriteId::WALL3, {192, 64}},
				{proto::SpriteId::WALL4, {384, 110}},
				{proto::SpriteId::WALL5, {384, 58}},
				{proto::SpriteId::WALL6, {96, 142}},
				{proto::SpriteId::WALL7, {868, 16}},
				{proto::SpriteId::WALL8, {128, 110}},
				{proto::SpriteId::WALL_ROTATE1, {192, 96}},
				{proto::SpriteId::WALL_ROTATE2, {128, 94}},
				{proto::SpriteId::WALL_ROTATE3, {192, 64}},
				{proto::SpriteId::WALL_ROTATE4, {384, 110}},
				{proto::SpriteId::WALL_ROTATE5, {384, 58}},
				{proto::SpriteId::WALL_ROTATE6, {96, 142}},
				{proto::SpriteId::WALL_ROTATE7, {868, 16}},
				{proto::SpriteId::WALL_ROTATE8, {128, 110}},
			};
	};
}}