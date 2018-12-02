/*
** EPITECH PROJECT, 2021
** server
** File description:
** Created by seb,
*/

#pragma once

#include "Network/GameProtocol.hpp"
#include "ecs/Entity.hpp"

namespace ecs { namespace component {
	struct OnlineComponent {
		OnlineComponent() {}
		OnlineComponent(ID onlineId, proto::SpriteId spriteId) {
			this->onlineId = onlineId;
			this->spriteId = spriteId;
		}
		ID				onlineId;
		proto::SpriteId	spriteId;
	};
}}