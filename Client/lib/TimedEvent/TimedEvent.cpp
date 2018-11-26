//
// Created by seb on 10/10/18.
//

#include "TimedEvent.hpp"
#include <thread>
#include <iostream>

TimedEvent::TimedEvent(): _threadAlive(true),
	_thread([this](){
		long time;
		std::vector<TimedFuntion, std::allocator<TimedFuntion>>::iterator func;
		this->_mutexAlive.lock();
		while (_threadAlive) {
			this->_mutexAlive.unlock();
			time = getTime();
			this->_mutexFunctions.lock();
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
			_mutexFunctions.unlock();
			_mutexAlive.lock();
			std::this_thread::sleep_for(std::chrono::microseconds(16666/2));
		}
		this->_mutexAlive.unlock();
	})
{
	_initialTime = getTime();
}

TimedEvent::~TimedEvent() {
	_threadAlive = false;
	_thread.join();
}

TimedEvent& TimedEvent::get() {
	static TimedEvent event;

	return event;
}

long TimedEvent::getTime() {
	return (std::chrono::duration_cast<std::chrono::nanoseconds>(
		_clock.now().time_since_epoch()).count());
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

	_mutexFunctions.lock();
	_timedFunctions.emplace_back(TimedFuntion(getTime() + _time, function));
	_mutexFunctions.unlock();

}