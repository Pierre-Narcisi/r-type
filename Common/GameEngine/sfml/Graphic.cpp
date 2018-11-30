/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#include <system/graphical/Graphicals.hpp>
#include <menu/TextDisplay.hpp>
#include "Graphic.hpp"

namespace ecs {namespace graphical {
	Graphic& Graphic::get() {
		static Graphic graphic;

		return graphic;
	}

	void Graphic::update() {
		while (_window->pollEvent(_event)) {
			if (_event.type == sf::Event::Closed)
				_window->close();

			if (_event.type == sf::Event::EventType::TextEntered)
				ecs::component::TextInput(_event);
			system::Controls::UpdateKeyboards(_event);
			system::Controls::UpdateMouses(_event);
			system::Controls::UpdateControllers(_event);
		}

		ecs::system::Graphicals::UpdateGraphicals();

		_window->display();
		_window->clear(sf::Color::Black);
	}

	bool Graphic::isOpen() {
		return _window->isOpen();
	}
}}