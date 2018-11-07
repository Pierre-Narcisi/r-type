/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#include <cmath>
#include "component/control/Controller.hpp"
#include "Controls.hpp"
#include "ecs/Ecs.hpp"

namespace ecs {namespace system {

	void Controls::UpdateControllers(sf::Event &event) {
		auto &controllers = ecs::Ecs::getConponentList<component::Controller>().getComponentList();
		const float DEAD_ZONE = 0.2f;

		for (auto &controller : controllers) {

			/// Buttons handle

			controller.buttonA = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 0);
			controller.buttonX = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 2);
			controller.buttonY = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 3);
			controller.buttonB = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 1);

			controller.select = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 6);
			controller.start = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 7);
			controller.menu = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 8);

			controller.rightB = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 5);
			controller.leftB = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 4);

			controller.leftJoyB = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 9);
			controller.leftJoyB = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 10);

			/// LEFT ROTATION
			float rotHorizontal =
				sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::Axis::X) / 100.f;
			if((rotHorizontal < 0 ? -rotHorizontal : rotHorizontal) < DEAD_ZONE)
				rotHorizontal = 0.f;
			float rotVertical =
				sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::Axis::Y) / -100.f;
			if((rotVertical < 0 ? -rotVertical : rotVertical) < DEAD_ZONE)
				rotVertical = 0.f;

			if (rotHorizontal == 0 && rotVertical == 0) {
				controller.joystickLeftState = false;
				controller.joystickLeft = 90.f;
			}
			else {
				controller.joystickLeftState = true;
				float rot = static_cast<float>(atan(rotVertical/rotHorizontal) / M_PI * 180.0);
				if (rotHorizontal > 0) {
					if (rotVertical > 0)
						controller.joystickLeft = 360.f - rot;
					else
						controller.joystickLeft = -rot;
				} else {
					controller.joystickLeft = 180 - rot;
				}
				if (rotVertical == 1)
					controller.joystickLeft = 270;
				else if (rotVertical == -1)
					controller.joystickLeft = 90;
			}

			/// RIGHT ROTATION
			rotHorizontal =
				sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::Axis::U) / 100.f;
			if((rotHorizontal < 0 ? -rotHorizontal : rotHorizontal) < DEAD_ZONE)
				rotHorizontal = 0.f;
			rotVertical =
				sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::Axis::V) / -100.f;
			if((rotVertical < 0 ? -rotVertical : rotVertical) < DEAD_ZONE)
				rotVertical = 0.f;

			if (rotHorizontal == 0.f && rotVertical == 0.f) {
				controller.joystickRightState = false;
				controller.joystickRight = 90.f;
			} else {
				controller.joystickRightState = true;
				float rot = static_cast<float>(atan(rotVertical/rotHorizontal) / M_PI * 180.0);
				if (rotHorizontal > 0) {
					if (rotVertical > 0)
						controller.joystickRight = 360.f - rot;
					else
						controller.joystickRight = -rot;
				} else {
					controller.joystickRight = 180 - rot;
				}
				if (rotVertical == 1)
					controller.joystickRight = 270;
				else if (rotVertical == -1)
					controller.joystickRight = 90;
			}
		}
	}

	void Controls::UpdateKeyboards(sf::Event &event) {
		auto &keyboards = ecs::Ecs::getConponentList<component::Keyboard>().getComponentList();

		for (auto &keyboard : keyboards) {
			for (auto it = keyboard.keyMap.begin(); it != keyboard.keyMap.end(); it++) {
				if (sf::Keyboard::isKeyPressed(Controls::getKeyBoard()[it->first]))
					keyboard.keyMap[it->first]();
			}
		}
	}

	void Controls::UpdateMouses(sf::Event &event) {
		auto &mouses = ecs::Ecs::getConponentList<component::Mouse>().getComponentList();

		for (auto &mouse : mouses) {
			for (auto it = mouse.mouseMap.begin(); it != mouse.mouseMap.end(); it++) {
				if (sf::Mouse::isButtonPressed(
					Controls::getMouse()[it->first]))
					mouse.mouseMap[it->first]();
			}
			if (event.type == sf::Event::EventType::MouseMoved) {
				mouse.position.x = event.mouseMove.x;
				mouse.position.y = event.mouseMove.y;
			}
		}
	}

}}