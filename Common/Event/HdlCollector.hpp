/*
 * --------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <benjamin.viguier@epitech.eu> wrote this file. As long as you retain this 
 * notice you can do whatever you want with this stuff. If we meet some day,
 * and you think this stuff is worth it, you can buy me a beer in
 * return Benjamin Viguier
 * --------------------------------------------------------------------------
 */

#pragma once

#include "Event/Event.hpp"

namespace evt
{
	class HdlCollector
	{
	public:
		HdlCollector(void) = default;
		~HdlCollector();

		Event::EvtHdlDestr
				add(Event::EvtHdlDestr const &);
		HdlCollector	&operator<<(Event::EvtHdlDestr const &);

		void	flush(void);
	private:
		std::list<Event::EvtHdlDestr const *>	_unregisterEventsHdls;
	};
}