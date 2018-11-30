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
#include "component/control/Controller.hpp"
#include "Controls.hpp"
#include "ecs/Ecs.hpp"
#include "../../component/control/Controller.hpp"
#include "../../ecs/Ecs.hpp"

namespace ecs {namespace system {

	void Controls::UpdateControllers(sf::Event &event) {
		auto &controllers = ecs::Ecs::getComponentMap<component::Controller>();
		const float DEAD_ZONE = 0.2f;

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

	void Controls::UpdateKeyboards(sf::Event &event) {
		auto &keyboards = ecs::Ecs::getComponentMap<component::Keyboard>();

		for (auto &keyboard : keyboards) {
			for (auto it = keyboard.second.keyMap.begin(); it != keyboard.second.keyMap.end(); it++) {
				if (sf::Keyboard::isKeyPressed(Controls::getKeyBoard()[it->first])) {
					keyboard.second.keyMap[it->first].first = true;
				} else {
					keyboard.second.keyMap[it->first].first = false;
				}
				if (keyboard.second.keyMap[it->first].first && keyboard.second.keyMap[it->first].second)
					keyboard.second.keyMap[it->first].second(keyboard.first);
			}
		}
	}

	void Controls::UpdateMouses(sf::Event &event) {
		auto &mouses = ecs::Ecs::getComponentMap<component::Mouse>();

		for (auto &mouse : mouses) {
			for (auto it = mouse.second.mouseMap.begin(); it != mouse.second.mouseMap.end(); it++) {
				if (sf::Mouse::isButtonPressed(Controls::getMouse()[it->first])) {
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

	void Controls::UpdateDeplacement() {
		auto deplacements = ecs::Ecs::filter<component::Keyboard, component::DeplacementKeyBoard, component::Speed>();
		float time;

		for (auto tomove : deplacements) {
			auto &keyB = ecs::Ecs::getComponentMap<component::Keyboard>()[tomove];
			auto &dep = ecs::Ecs::getComponentMap<component::DeplacementKeyBoard>()[tomove];
			core::Vector2<float> deplacement(0.f, 0.f);

			if (keyB.keyMap[dep.forward].first)
				deplacement.y = -dep.speed;
			else if (keyB.keyMap[dep.backward].first)
				deplacement.y = dep.speed;
			if (keyB.keyMap[dep.left].first)
				deplacement.x = -dep.speed;
			else if (keyB.keyMap[dep.right].first)
				deplacement.x = dep.speed;

			if (keyB.keyMap[dep.forward].first && keyB.keyMap[dep.left].first) {
				deplacement.y = -(dep.speed * 0.7071);
				deplacement.x = -(dep.speed * 0.7071);
			}
			if (keyB.keyMap[dep.forward].first && keyB.keyMap[dep.right].first) {
				deplacement.y = -(dep.speed * 0.7071);
				deplacement.x = (dep.speed * 0.7071);
			}
			if (keyB.keyMap[dep.backward].first && keyB.keyMap[dep.left].first) {
				deplacement.y = (dep.speed * 0.7071);
				deplacement.x = -(dep.speed * 0.7071);
			}
			if (keyB.keyMap[dep.backward].first && keyB.keyMap[dep.right].first) {
				deplacement.y = (dep.speed * 0.7071);
				deplacement.x = (dep.speed * 0.7071);
			}
			time = static_cast<float>(ecs::core::Time::get(TimeUnit::MicroSeconds) - dep.lastMove);
			ecs::Ecs::getComponentMap<component::Speed>()[tomove].x = time / 1000000.f * deplacement.x;
			ecs::Ecs::getComponentMap<component::Speed>()[tomove].y = time / 1000000.f * deplacement.y;
			dep.lastMove = ecs::core::Time::get(TimeUnit::MicroSeconds);
		}

		auto mouses = ecs::Ecs::filter<component::Mouse, component::Speed, component::DeplacementMouse, component::Position>();
		auto &mouseMap = ecs::Ecs::getComponentMap<component::Mouse>();
		auto &mouseDepMap = ecs::Ecs::getComponentMap<component::DeplacementMouse>();
		auto &speedMap = ecs::Ecs::getComponentMap<component::Speed>();
		auto &posMap = ecs::Ecs::getComponentMap<component::Position>();
		for (auto mouse : mouses) {
			mouseDepMap[mouse].lastPosition.x = posMap[mouse].x;
			mouseDepMap[mouse].lastPosition.y = posMap[mouse].y;
			if (!(mouseMap[mouse].position == mouseDepMap[mouse].lastPosition)) {
				if (abs(mouseMap[mouse].position.x - mouseDepMap[mouse].lastPosition.x) + abs(mouseMap[mouse].position.y - mouseDepMap[mouse].lastPosition.y) < mouseDepMap[mouse].speed) {
					speedMap[mouse].x = mouseMap[mouse].position.x - mouseDepMap[mouse].lastPosition.x;
					speedMap[mouse].y = mouseMap[mouse].position.y - mouseDepMap[mouse].lastPosition.y;
				} else {
					auto total = abs(mouseMap[mouse].position.x - mouseDepMap[mouse].lastPosition.x) + abs(mouseMap[mouse].position.y - mouseDepMap[mouse].lastPosition.y);
					speedMap[mouse].x = mouseDepMap[mouse].speed * (mouseMap[mouse].position.x - mouseDepMap[mouse].lastPosition.x) / total;
					speedMap[mouse].y = mouseDepMap[mouse].speed * (mouseMap[mouse].position.y - mouseDepMap[mouse].lastPosition.y) / total;
				}
			} else {
				speedMap[mouse].x = 0.f;
				speedMap[mouse].y = 0.f;
			}
			time = static_cast<float>(ecs::core::Time::get(TimeUnit::MicroSeconds) - mouseDepMap[mouse].lastMove);
			speedMap[mouse].x = time / 1000000.f * speedMap[mouse].x;
			speedMap[mouse].y = time / 1000000.f * speedMap[mouse].y;
			mouseDepMap[mouse] = time;
		}
	}

}}