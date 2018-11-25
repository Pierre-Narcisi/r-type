/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** JsonBuilder.cpp
*/

#include <sstream>
#include "JsonBuilder.hpp"
#include "Json/Parser.hpp"

namespace common {

std::list<json::Entity>	JsonBuider::_extractJsonObjects(std::size_t available) {
	auto pos = _buffer.size();

	_buffer.resize(_buffer.size() + available);
	_socket.read(&_buffer.front() + pos, available);

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

			std::memmove(&_buffer.front(), (void*) start, len);
			_buffer.resize(len);
		} 
	return (res);
}

}