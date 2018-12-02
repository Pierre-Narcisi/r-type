/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

#include <SFML/Window/Event.hpp>
#include <unordered_map>
#include "component/control/Keyboard.hpp"
#include "component/control/Mouse.hpp"

namespace ecs {namespace system {
	class ControlsSFML {
	public:
		ControlsSFML() {
			this->mapMouseKeys = {
				{KeyMouse::LCLICK, sf::Mouse::Left},
				{KeyMouse::RCLICK, sf::Mouse::Right},
				{KeyMouse::MCLICK, sf::Mouse::Middle}
			};

			this->mapKeyboardKeys = {
				{KeyKeyboard::KEY_A,       sf::Keyboard::A},
				{KeyKeyboard::KEY_B,       sf::Keyboard::B},
				{KeyKeyboard::KEY_C,       sf::Keyboard::C},
				{KeyKeyboard::KEY_D,       sf::Keyboard::D},
				{KeyKeyboard::KEY_E,       sf::Keyboard::E},
				{KeyKeyboard::KEY_F,       sf::Keyboard::F},
				{KeyKeyboard::KEY_G,       sf::Keyboard::G},
				{KeyKeyboard::KEY_H,       sf::Keyboard::H},
				{KeyKeyboard::KEY_I,       sf::Keyboard::I},
				{KeyKeyboard::KEY_J,       sf::Keyboard::J},
				{KeyKeyboard::KEY_K,       sf::Keyboard::K},
				{KeyKeyboard::KEY_L,       sf::Keyboard::L},
				{KeyKeyboard::KEY_M,       sf::Keyboard::M},
				{KeyKeyboard::KEY_N,       sf::Keyboard::N},
				{KeyKeyboard::KEY_O,       sf::Keyboard::O},
				{KeyKeyboard::KEY_P,       sf::Keyboard::P},
				{KeyKeyboard::KEY_Q,       sf::Keyboard::Q},
				{KeyKeyboard::KEY_R,       sf::Keyboard::R},
				{KeyKeyboard::KEY_S,       sf::Keyboard::S},
				{KeyKeyboard::KEY_T,       sf::Keyboard::T},
				{KeyKeyboard::KEY_U,       sf::Keyboard::U},
				{KeyKeyboard::KEY_V,       sf::Keyboard::V},
				{KeyKeyboard::KEY_W,       sf::Keyboard::W},
				{KeyKeyboard::KEY_X,       sf::Keyboard::X},
				{KeyKeyboard::KEY_Y,       sf::Keyboard::Y},
				{KeyKeyboard::KEY_Z,       sf::Keyboard::Z},
				{KeyKeyboard::KEY_0,       sf::Keyboard::Num0},
				{KeyKeyboard::KEY_1,       sf::Keyboard::Num1},
				{KeyKeyboard::KEY_2,       sf::Keyboard::Num2},
				{KeyKeyboard::KEY_3,       sf::Keyboard::Num3},
				{KeyKeyboard::KEY_4,       sf::Keyboard::Num4},
				{KeyKeyboard::KEY_5,       sf::Keyboard::Num5},
				{KeyKeyboard::KEY_6,       sf::Keyboard::Num6},
				{KeyKeyboard::KEY_7,       sf::Keyboard::Num7},
				{KeyKeyboard::KEY_8,       sf::Keyboard::Num8},
				{KeyKeyboard::KEY_9,       sf::Keyboard::Num9},
				{KeyKeyboard::KEY_F1,      sf::Keyboard::F1},
				{KeyKeyboard::KEY_F2,      sf::Keyboard::F2},
				{KeyKeyboard::KEY_F3,      sf::Keyboard::F3},
				{KeyKeyboard::KEY_F4,      sf::Keyboard::F4},
				{KeyKeyboard::KEY_F5,      sf::Keyboard::F5},
				{KeyKeyboard::KEY_F6,      sf::Keyboard::F6},
				{KeyKeyboard::KEY_F7,      sf::Keyboard::F7},
				{KeyKeyboard::KEY_F8,      sf::Keyboard::F8},
				{KeyKeyboard::KEY_F9,      sf::Keyboard::F9},
				{KeyKeyboard::KEY_F10,     sf::Keyboard::F10},
				{KeyKeyboard::KEY_F11,     sf::Keyboard::F11},
				{KeyKeyboard::KEY_F12,     sf::Keyboard::F12},
				{KeyKeyboard::ESCAPE,      sf::Keyboard::Escape},
				{KeyKeyboard::SPACE,       sf::Keyboard::Space},
				{KeyKeyboard::LCTRL,       sf::Keyboard::LControl},
				{KeyKeyboard::RCTRL,       sf::Keyboard::RControl},
				{KeyKeyboard::LSHIFT,      sf::Keyboard::LShift},
				{KeyKeyboard::RSHIFT,      sf::Keyboard::RShift},
				{KeyKeyboard::ENTER,       sf::Keyboard::Return},
				{KeyKeyboard::LEFT_ARROW,  sf::Keyboard::Left},
				{KeyKeyboard::RIGHT_ARROW, sf::Keyboard::Right},
				{KeyKeyboard::UP_ARROW,    sf::Keyboard::Up},
				{KeyKeyboard::DOWN_ARROW,  sf::Keyboard::Down}
			};
		}

		static ControlsSFML &get() {
			thread_local static ControlsSFML controls;

			return controls;
		}

		static std::unordered_map<KeyKeyboard, sf::Keyboard::Key> &getKeyBoard() {
			return get().mapKeyboardKeys;
		}

		static std::unordered_map<KeyMouse , sf::Mouse::Button> &getMouse() {
			return get().mapMouseKeys;
		}

		static void UpdateControllers(sf::Event &event);
//		static void UpdateControllers();
		static void UpdateKeyboardsEvent(sf::Event &event);
		static void UpdateMousesEvents(sf::Event &event);

	private:
		std::unordered_map<KeyKeyboard, sf::Keyboard::Key>	mapKeyboardKeys;
		std::unordered_map<KeyMouse , sf::Mouse::Button>	mapMouseKeys;
	};
}}