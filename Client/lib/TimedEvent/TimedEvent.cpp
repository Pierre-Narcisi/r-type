//
// Created by seb on 10/10/18.
//

#include "TimedEvent.hpp"
#include "ecs/Ecs.hpp"
#include "core/Time.hpp"
#include <thread>
#include <iostream>

TimedEvent::TimedEvent()
{
	ecs::Ecs::get().addUpdate(10, [this](){
		long time;
		std::vector<TimedFuntion, std::allocator<TimedFuntion>>::iterator func;
		time = ecs::core::Time::get(TimeUnit::NanoSeconds);
		func = this->_timedFunctions.begin();
		if (this->_timedFunctions.empty() != 1) {
			while (func != this->_timedFunctions.end()) {
				if (func->time > this->_initialTime && func->time < time) {
					func->func();
					_timedFunctions.erase(func);
					func--;
				}
				func++;
			}
		}
	});
	_initialTime = ecs::core::Time::get(TimeUnit::NanoSeconds);
}

TimedEvent::~TimedEvent() {
}

TimedEvent& TimedEvent::get() {
	static TimedEvent event;

	return event;
}

void TimedEvent::addEvent(long time, Time unit, std::function<void()> function) {
	long _time;

	if (unit == Time::Hours)
		_time = time * 3600000000000;
	else if (unit == Time::Minutes)
		_time = time * 60000000000;
	else if (unit == Time::Seconds)
		_time = time * 1000000000;
	else if (unit == Time::MilliSeconds)
		_time = time * 1000000;
	else if (unit == Time::MicroSeconds)
		_time = time * 1000;
	else
		_time = time;

	_timedFunctions.emplace_back(TimedFuntion(ecs::core::Time::get(TimeUnit::NanoSeconds) + _time, function));

}