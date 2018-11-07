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

	void Graphic::update() {
		while (_window->pollEvent(_event)) {
			if (_event.type == sf::Event::Closed)
				_window->close();

			if (_event.type == sf::Event::EventType::TextEntered ||
			    _event.type == sf::Event::EventType::KeyPressed ||
			    _event.type == sf::Event::EventType::KeyReleased) {
				system::Controls::UpdateKeyboards(_event);
			} else if (_event.type == sf::Event::EventType::MouseButtonPressed ||
				_event.type == sf::Event::EventType::MouseMoved) {
				system::Controls::UpdateMouses(_event);
			} else if (_event.type == sf::Event::EventType::JoystickButtonPressed ||
				   _event.type == sf::Event::EventType::JoystickButtonReleased ||
				   _event.type == sf::Event::EventType::JoystickMoved) {
				system::Controls::UpdateControllers(_event);
			}
		}

		for (auto it = _spriteMap.begin(); it != _spriteMap.end(); it++) {
			if (it->second.visible) {
				_window->draw(*it->second.sprite);
			}
		}

		_window->display();
		_window->clear(sf::Color::Black);
	}

	bool Graphic::isOpen() {
		return _window->isOpen();
	}

	unsigned long Graphic::createSprite(std::string path) {
		unsigned long id = _lastId;
		_spriteMap[id].texture = new sf::Texture();

		if (!_spriteMap[id].texture->loadFromFile(path)) {
			_spriteMap.erase(id);
			return 0;
		}
		_lastId++;
		_spriteMap[id].sprite = new sf::Sprite(*_spriteMap[id].texture);
		_spriteMap[id].size = getTextureSize(path);
		_spriteMap[id].sprite->setOrigin(_spriteMap[id].size.x / 2, _spriteMap[id].size.y / 2);
		_spriteMap[id].sprite->setPosition(_spriteMap[id].size.x / 2, _spriteMap[id].size.y / 2);
		_spriteMap[id].pos = core::Vector2<float>(0,0);
		_spriteMap[id].visible = true;
		_layers[1].push_back(id);
		return (id);
	}

	core::Vector2<unsigned int> Graphic::getTextureSize(std::string path) {
		sf::Texture tmp;

		if (!tmp.loadFromFile(path))
			return core::Vector2<unsigned int>();
		auto size = tmp.getSize();
		return core::Vector2<unsigned int>(size.x, size.y);
	}
}}