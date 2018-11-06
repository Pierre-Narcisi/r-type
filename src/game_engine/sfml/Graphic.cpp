/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#include "Graphic.hpp"

namespace ecs {namespace graphical {
	Graphic& Graphic::get() {
		static Graphic graphic;

		return graphic;
	}
}}