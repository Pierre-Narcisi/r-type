/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

namespace ecs {namespace core {
	template <typename T>
	struct Vector2 {
		Vector2();
		Vector2(T x, T y) {
			this->x = x;
			this->y = y;
		}
		T x;
		T y;
	};

	template <typename T>
	struct Vector3 {
		Vector3();
		Vector3(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
		T x;
		T y;
		T z;
	};

	template <typename T>
	struct Vector4 {
		Vector4();
		Vector4(T xa, T ya, T xb, T yb) {
			this->xa = xa;
			this->ya = ya;
			this->xb = xb;
			this->yb = yb;
		}
		T xa;
		T ya;
		T xb;
		T yb;
	};
}}