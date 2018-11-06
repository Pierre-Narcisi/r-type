/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

#include <string>

namespace ecs {namespace component {
	struct Controller {
		int 		id;
		float		joystickLeft;
		bool 		joystickLeftState;
		float		joystickRight;
		bool 		joystickRightState;
		bool 		rightT;
		bool 		rightB;
		bool 		leftT;
		bool 		leftB;
		bool 		leftJoyB;
		bool 		rightJoyB;
		bool 		buttonY;
		bool 		buttonX;
		bool 		buttonB;
		bool 		buttonA;
		bool 		arrowL;
		bool 		arrowR;
		bool 		arrowU;
		bool 		arrowD;
		bool 		select;
		bool 		start;
		bool 		menu;
	};
}}