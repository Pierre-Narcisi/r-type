/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

#include <string>
#include <iostream>
#include <sfml/Graphic.hpp>

#include "../../game_engine/ecs/Ecs.hpp"
#include "../../game_engine/sfml/Graphic.hpp"

namespace ecs {namespace component {
	struct TextDisplay {
		TextDisplay() {
		}

		TextDisplay(std::string path, std::string str) {
			_str = str;
			_font = new sf::Font();
			_font->loadFromFile(path);
			_text = new sf::Text(_str, *_font);
			_text->setCharacterSize(_size);
			_text->setFillColor(_color);
		}

		TextDisplay(std::string path, std::string str, float posX, float posY) {
			_str = str;
			_pos.x = posX;
			_pos.y = posY;
			_font = new sf::Font();
			_font->loadFromFile(path);
			_text = new sf::Text(_str, *_font);
			_text->setCharacterSize(_size);
			_text->setFillColor(_color);
			_text->setOrigin(_text->getLocalBounds().width/2, _text->getLocalBounds().height/2);
		}

		TextDisplay(std::string path, std::string str, float posX, float posY, bool input) {
			_input = input;
			_str = str;
			_pos.x = posX;
			_pos.y = posY;
			_font = new sf::Font();
			_font->loadFromFile(path);
			_text = new sf::Text(_str, *_font);
			_text->setCharacterSize(_size);
			_text->setFillColor(_color);
			_text->setOrigin(_text->getLocalBounds().width/2, _text->getLocalBounds().height/2);
		}

		TextDisplay(std::string path, std::string str, float posX, float posY, bool input, sf::Color color, int size) {
			_input = input;
			_color = color;
			_size = size;
			_str = str;
			_pos.x = posX;
			_pos.y = posY;
			_font = new sf::Font();
			_font->loadFromFile(path);
			_text = new sf::Text(_str, *_font);
			_text->setCharacterSize(_size);
			_text->setFillColor(_color);
			_text->setOrigin(_text->getLocalBounds().width/2, _text->getLocalBounds().height/2);
		}

		~TextDisplay() {
			delete _font;
			delete _text;
		}


        sf::Font                *_font;
        sf::Text                *_text;
		sf::Color				_color = sf::Color::White;

        std::string             _str;
        unsigned int            _size = 20;
		bool					_input = false;
		ecs::core::Vector2<float>		_pos = {0, 0};
	};

	inline void TextInput(sf::Event _event)
	{
		auto ids = ecs::Ecs::filter<TextDisplay>();
        auto &txt = ecs::Ecs::getComponentMap<TextDisplay>();

		for (auto id : ids) {
		if (_event.type == sf::Event::TextEntered && txt[id]._input == true)
		{
			if ((_event.text.unicode <= 122 && _event.text.unicode >= 97) || _event.text.unicode == 45 || _event.text.unicode == 95)
        		txt[id]._str += static_cast<char>(_event.text.unicode);
			if (_event.text.unicode <= 90 && _event.text.unicode >= 65)
        		txt[id]._str += static_cast<char>(_event.text.unicode);
			if (_event.text.unicode <= 57 && _event.text.unicode >= 48)
        		txt[id]._str += static_cast<char>(_event.text.unicode);
			if (_event.text.unicode == 8)
				txt[id]._str = txt[id]._str.substr(0, txt[id]._str.size()-1);
		}
		}
	}


	/*inline void UpdateTextDisplay()
	{
        auto ids = ecs::Ecs::filter<TextDisplay>();
        auto window = ecs::graphical::Graphic::getWindow();
        auto &txt = ecs::Ecs::getComponentMap<TextDisplay>();

        for (auto id : ids) {
			txt[id]._text->setString(txt[id]._str);
			txt[id]._text->setPosition(txt[id]._pos.x, txt[id]._pos.y);
			txt[id]._text->setOrigin(txt[id]._text->getLocalBounds().width/2, txt[id]._text->getLocalBounds().height/2);
			window->draw(*txt[id]._text);
        }
    }*/
}}