/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** MessageBox.hpp
*/

#if !defined(_MESSAGEBOX_HPP)
#define _MESSAGEBOX_HPP

#include "sfml/Graphic.hpp"

namespace rtype {

class MsgBox {
public:
	static void show(std::string const &title, std::string const &message) {
		sf::Font font;
		if (!font.loadFromFile("assets/Font/Quicksand-Bold.otf")) {
			std::cout << "Couldn't load font" << std::endl;
			exit(84);
		}

		sf::Text text;
		text.setFont(font);
		text.setString(message);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		auto s = text.getLocalBounds();

		sf::VideoMode mode;
		mode.width = s.width + 50;
		mode.height = s.height + 25;
		mode.bitsPerPixel = 32;
		auto *_window = new sf::RenderWindow(mode, title, sf::Style::Resize | sf::Style::Close);
		sf::Event _event;

		text.setPosition((mode.width - s.width) / 2.f, 5.f);

		while (_window->isOpen()) {
			while (_window->pollEvent(_event))
				if (_event.type == sf::Event::Closed)
					_window->close();
			_window->clear(sf::Color::White);
			_window->draw(text);
			_window->display();
			_window->clear();
		}
		delete _window;
	}
};

}

#endif // _MESSAGEBOX_HPP
