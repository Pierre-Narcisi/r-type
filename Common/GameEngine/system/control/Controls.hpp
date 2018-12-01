/*
** EPITECH PROJECT, 2021
** server
** File description:
** Created by seb,
*/

#pragma once

namespace ecs { namespace system {

	class Controls {
	public:
		static void UpdateKeyboards();

		static void UpdateMouses();

		static void UpdateDeplacement();
	};

}}
