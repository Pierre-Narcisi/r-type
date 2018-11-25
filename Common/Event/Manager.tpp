/*
 * --------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <benjamin.viguier@epitech.eu> wrote this file. As long as you retain this 
 * notice you can do whatever you want with this stuff. If we meet some day,
 * and you think this stuff is worth it, you can buy me a beer in
 * return Benjamin Viguier
 * --------------------------------------------------------------------------
 */

#include <iostream>
#include <sstream>
#include <utility>
#include "Manager.hpp"

namespace evt
{
	template<typename T>
	void	BasicManager<T>::removeEvent(T const &eventName)
	{
		_events.erase(eventName);
	}

#ifdef DEBUG_ON
	template<typename T>
	void	BasicManager<T>::dump() const
	{
		for (auto event : _events) {
			std::cout << "evt[" << event.first << "]" << " = ";
			event.second.dump();
			std::cout << std::endl;
		}
	}
#endif
	
	template<typename T>
	EventWrapper
	BasicManager<T>::operator[](T const &eventName)
	{
		auto	rIt = _events.find(eventName);
		Event	*_evt;

		if (rIt == _events.end()) {
			auto it = _events.insert(std::make_pair(
				eventName,
				Event([this, eventName] {
					this->removeEvent(eventName);
				})
			));

			_evt = &(it.first->second);
		} else {
			_evt = &(rIt->second);
		}
		return EventWrapper(*_evt, [this, eventName, _evt] (void) {
			if (_events.find(eventName) != _events.end() &&
			    _evt->isEmpty())
				this->removeEvent(eventName);
		});
	}

	template<typename T>
	inline BasicManager<T>	&BasicManager<T>::get(void)
	{
			static BasicManager<T>	manager;
			return (manager);
	}
}