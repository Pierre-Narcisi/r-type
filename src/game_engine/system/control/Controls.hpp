/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

namespace ecs {namespace system {
	class Controls {
		static void UpdateControllers(sf::event &event);
		static void UpdateKeyboards(sf::event &event);
		static void UpdateMouses(sf::event &event);
	};
}}