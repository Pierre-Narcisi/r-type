/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#define _USE_MATH_DEFINES
#include <cmath>
#include <component/control/DeplacementKeyBoard.hpp>
#include <component/physic/Position.hpp>
#include <component/physic/Speed.hpp>
#include <component/control/DeplacementMouse.hpp>
#include <component/control/LazyDeplacementMouse.hpp>
#include "component/control/Controller.hpp"
#include "ControlsSFML.hpp"
#include "ecs/Ecs.hpp"
#include "../../component/control/Controller.hpp"
#include "../../ecs/Ecs.hpp"

namespace ecs {namespace system {

	void ControlsSFML::UpdateControllers(sf::Event &event) {
		auto &controllers = ecs::Ecs::getComponentMap<component::Controller>();
		const float DEAD_ZONE = 0.2f;

		if (!(event.type == sf::Event::EventType::JoystickButtonPressed ||
				   event.type == sf::Event::EventType::JoystickButtonReleased ||
				   event.type == sf::Event::EventType::JoystickMoved))
			return;

		for (auto &controller : controllers) {

			/// Buttons handle

			controller.second.buttonA = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 0);
			controller.second.buttonX = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 2);
			controller.second.buttonY = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 3);
			controller.second.buttonB = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 1);

			controller.second.select = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 6);
			controller.second.start = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 7);
			controller.second.menu = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 8);

			controller.second.rightB = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 5);
			controller.second.leftB = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 4);

			controller.second.leftJoyB = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 9);
			controller.second.leftJoyB = sf::Joystick::isButtonPressed(event.joystickButton.joystickId, 10);

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
				controller.second.joystickLeftState = false;
				controller.second.joystickLeft = 90.f;
			}
			else {
				controller.second.joystickLeftState = true;
				float rot = static_cast<float>(atan(rotVertical/rotHorizontal) / M_PI * 180.0);
				if (rotHorizontal > 0) {
					if (rotVertical > 0)
						controller.second.joystickLeft = 360.f - rot;
					else
						controller.second.joystickLeft = -rot;
				} else {
					controller.second.joystickLeft = 180 - rot;
				}
				if (rotVertical == 1)
					controller.second.joystickLeft = 270;
				else if (rotVertical == -1)
					controller.second.joystickLeft = 90;
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
				controller.second.joystickRightState = false;
				controller.second.joystickRight = 90.f;
			} else {
				controller.second.joystickRightState = true;
				float rot = static_cast<float>(atan(rotVertical/rotHorizontal) / M_PI * 180.0);
				if (rotHorizontal > 0) {
					if (rotVertical > 0)
						controller.second.joystickRight = 360.f - rot;
					else
						controller.second.joystickRight = -rot;
				} else {
					controller.second.joystickRight = 180 - rot;
				}
				if (rotVertical == 1)
					controller.second.joystickRight = 270;
				else if (rotVertical == -1)
					controller.second.joystickRight = 90;
			}
		}
	}

	void ControlsSFML::UpdateKeyboardsEvent(sf::Event &event) {
		auto &keyboards = ecs::Ecs::getComponentMap<component::Keyboard>();

		for (auto &keyboard : keyboards) {
			for (auto it = keyboard.second.keyMap.begin(); it != keyboard.second.keyMap.end(); it++) {
				if (sf::Keyboard::isKeyPressed(ControlsSFML::getKeyBoard()[it->first])) {
					keyboard.second.keyMap[it->first].first = true;
				} else {
					keyboard.second.keyMap[it->first].first = false;
				}
			}
		}
	}

	void ControlsSFML::UpdateMousesEvents(sf::Event &event) {
		auto &mouses = ecs::Ecs::getComponentMap<component::Mouse>();

		for (auto &mouse : mouses) {
			for (auto it = mouse.second.mouseMap.begin(); it != mouse.second.mouseMap.end(); it++) {
				if (sf::Mouse::isButtonPressed(ControlsSFML::getMouse()[it->first])) {
					mouse.second.mouseMap[it->first].first = true;
				} else {
					mouse.second.mouseMap[it->first].first = false;
				}
				if (mouse.second.mouseMap[it->first].first && mouse.second.mouseMap[it->first].second)
					mouse.second.mouseMap[it->first].second(mouse.first);
			}
			if (event.type == sf::Event::EventType::MouseMoved) {
				mouse.second.position.x = event.mouseMove.x;
				mouse.second.position.y = event.mouseMove.y;
			}
		}
	}

}}
