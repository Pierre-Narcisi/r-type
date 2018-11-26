/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** JsonBuilder.cpp
*/

#include <sstream>
#include "JsonBuilder.hpp"
#include "Json/Parser.hpp"

// #include <iostream>

namespace common {

std::list<json::Entity>	JsonBuider::_extractJsonObjects(std::size_t available) {
	auto pos = _buffer.size();

	_buffer.resize(_buffer.size() + available);
	_socket.read(&_buffer.front() + pos, available);

	//std::cout << (void*) &_buffer.front() << std::endl;

	std::istringstream		sstm(std::string(_buffer.begin(), _buffer.end()));
	std::list<json::Entity>	res;
	auto					lastPos = sstm.tellg();

	try {
		while (true) {
			json::Entity entity;
		
			entity = json::Parser::fromStream(sstm);
			lastPos = sstm.tellg();
			res.push_back(entity);
		}	
	} catch (json::Parser::ParserException &e) {
		if (sstm.peek() != -1) {
			if (_onIllegalJson) _onIllegalJson(e);
			_buffer.clear();
			return (res);
		}
		auto	start = (std::uintptr_t) &_buffer.front() + lastPos;
		auto	len = (std::uintptr_t) &_buffer.back() - start;

		// std::cout << (std::uintptr_t) &_buffer.front() << " " <<
		// 		(std::uintptr_t) &_buffer.back() << " " <<
		// 		len <<  ' ';
		// for (auto c: _buffer)
		// 	std::cout << c;
		// std::cout << std::endl;
		std::memmove(&_buffer.front(), (void*) start, len);
		_buffer.resize(len);
	} 
	return (res);
}

}