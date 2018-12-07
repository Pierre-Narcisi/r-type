/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

#include <core/Time.hpp>
#include "Keyboard.hpp"

namespace ecs {namespace component {
	struct DeplacementKeyBoard {
		DeplacementKeyBoard() {
			this->forward = KeyKeyboard::KEY_Z;
			this->left = KeyKeyboard::KEY_Q;
			this->backward = KeyKeyboard::KEY_S;
			this->right = KeyKeyboard::KEY_D;
			this->speed = 500.f;
			this->lastMove = ecs::core::Time::get(TimeUnit::MicroSeconds);
		}
		DeplacementKeyBoard(float speed) {
			this->forward = KeyKeyboard::KEY_Z;
			this->left = KeyKeyboard::KEY_Q;
			this->backward = KeyKeyboard::KEY_S;
			this->right = KeyKeyboard::KEY_D;
			this->speed = speed;
			this->lastMove = ecs::core::Time::get(TimeUnit::MicroSeconds);
		}
		DeplacementKeyBoard(KeyKeyboard forward, KeyKeyboard left, KeyKeyboard backward, KeyKeyboard right) {
			this->forward = forward;
			this->left = left;
			this->backward = backward;
			this->right = right;
			this->speed = 500.f;
			this->lastMove = ecs::core::Time::get(TimeUnit::MicroSeconds);
		}
		DeplacementKeyBoard(KeyKeyboard forward, KeyKeyboard left, KeyKeyboard backward, KeyKeyboard right, float speed) {
			this->forward = forward;
			this->left = left;
			this->backward = backward;
			this->right = right;
			this->speed = speed;
			this->lastMove = ecs::core::Time::get(TimeUnit::MicroSeconds);
		}

		KeyKeyboard	forward;
		KeyKeyboard	left;
		KeyKeyboard 	backward;
		KeyKeyboard	right;
		float		speed;
		long 		lastMove;
	};
}}