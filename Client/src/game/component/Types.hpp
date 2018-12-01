//
// Created by pierre on 20/11/2018.
//

#pragma once

namespace game {namespace component {
	struct Type {
		enum class Types {
			NONE,
			SHIP,
			ENEMY,
			BULLET_ENEMY,
			BULLET_SHIP,
			BONUS,
			WALL
		};
		Type() {
			_type = Types::NONE;
		}
		Type(Types type) {
			_type = type;
		}
		Types _type;
	};
}}
