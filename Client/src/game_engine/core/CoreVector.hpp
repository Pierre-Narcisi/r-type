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
		Vector2() {}
		Vector2(T x, T y) {
			this->x = x;
			this->y = y;
		}
		T x;
		T y;

		Vector2<T> &operator=(Vector2<T> const &equal) {
			this->x = equal.x;
			this->y = equal.y;
			return *this;
		}

		bool operator==(Vector2<T> const& other) {
			return (this->x == other.x && this->y == other.y);
		}
	};

	template <typename T>
	struct Vector3 {
		Vector3() {}
		Vector3(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
		T x;
		T y;
		T z;

		Vector3<T> &operator=(Vector3<T> const &equal) {
			this->x = equal.x;
			this->y = equal.y;
			this->z = equal.z;
			return *this;
		}
		bool operator==(Vector3<T> const& other) {
			return (this->x == other.x && this->y == other.y && this->z == other.z);
		}
	};

	template <typename T>
	struct Vector4 {
		Vector4() {}
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

		Vector4<T> &operator=(Vector4<T> const &equal) {
			this->xa = equal.xa;
			this->ya = equal.ya;
			this->xb = equal.xb;
			this->yb = equal.yb;
			return *this;
		}
		bool operator==(Vector4<T> const& other) {
			return (this->xa == other.xa && this->ya == other.ya && this->xb == other.xb && this->yb == other.yb);
		}
	};
}}