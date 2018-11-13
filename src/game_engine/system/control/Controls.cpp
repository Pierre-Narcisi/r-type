/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#include <cmath>
#include <component/control/DeplacementKeyBoard.hpp>
#include <component/physic/Position.hpp>
#include <component/physic/Speed.hpp>
#include "component/control/Controller.hpp"
#include "Controls.hpp"
#include "ecs/Ecs.hpp"

namespace ecs {namespace system {

	void Controls::UpdateControllers(sf::Event &event) {
		auto &controllers = ecs::Ecs::getConponentMap<component::Controller>().getComponentList();
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
		auto &keyboards = ecs::Ecs::getConponentMap<component::Keyboard>().getComponentList();
		auto id = ecs::Ecs::getConponentMap<component::Keyboard>().getIdsList().begin();

		for (auto &keyboard : keyboards) {
			for (auto it = keyboard.keyMap.begin(); it != keyboard.keyMap.end(); it++) {
				if (sf::Keyboard::isKeyPressed(Controls::getKeyBoard()[it->first])) {
					keyboard.keyMap[it->first].first = true;
					if (keyboard.keyMap[it->first].second)
						keyboard.keyMap[it->first].second(*id);
				} else
					keyboard.keyMap[it->first].first = false;
			}
			id++;
		}
	}

	void Controls::UpdateMouses(sf::Event &event) {
		auto &mouses = ecs::Ecs::getConponentMap<component::Mouse>().getComponentList();

		for (auto &mouse : mouses) {
			for (auto it = mouse.mouseMap.begin(); it != mouse.mouseMap.end(); it++) {
				if (sf::Mouse::isButtonPressed(Controls::getMouse()[it->first])) {
					mouse.mouseMap[it->first].first = true;
					if (mouse.mouseMap[it->first].second)
						mouse.mouseMap[it->first].second();
				} else
					mouse.mouseMap[it->first].first = false;
			}
			if (event.type == sf::Event::EventType::MouseMoved) {
				mouse.position.x = event.mouseMove.x;
				mouse.position.y = event.mouseMove.y;
			}
		}
	}

	void Controls::UpdateDeplacement() {
		auto deplacements = ecs::Ecs::filter<component::Keyboard, component::DeplacementKeyBoard, component::Speed>();
		float time;

		for (auto tomove : deplacements) {
			auto &keyB = ecs::Ecs::getConponentMap<component::Keyboard>()[tomove];
			auto &dep = ecs::Ecs::getConponentMap<component::DeplacementKeyBoard>()[tomove];
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
			ecs::Ecs::getConponentMap<component::Speed>()[tomove].x = time / 1000000.f * deplacement.x;
			ecs::Ecs::getConponentMap<component::Speed>()[tomove].y = time / 1000000.f * deplacement.y;
			dep.lastMove = ecs::core::Time::get(TimeUnit::MicroSeconds);
		}
	}

}}