/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#include "Time.hpp"

namespace ecs {namespace core {
	long Time::get(TimeUnit unit) {
		static Time time;

		return time.got(unit);
	}

	long Time::got(TimeUnit unit) {
		if (unit == TimeUnit::Hours)
			return (std::chrono::duration_cast<std::chrono::hours>(_clock.now().time_since_epoch()).count());
		else if (unit == TimeUnit::Minutes)
			return (std::chrono::duration_cast<std::chrono::minutes>(_clock.now().time_since_epoch()).count());
		else if (unit == TimeUnit::Seconds)
			return (std::chrono::duration_cast<std::chrono::seconds>(_clock.now().time_since_epoch()).count());
		else if (unit == TimeUnit::MilliSeconds)
			return (std::chrono::duration_cast<std::chrono::milliseconds>(_clock.now().time_since_epoch()).count());
		else if (unit == TimeUnit::MicroSeconds)
			return (std::chrono::duration_cast<std::chrono::microseconds>(_clock.now().time_since_epoch()).count());
		else
			return (std::chrono::duration_cast<std::chrono::nanoseconds>(_clock.now().time_since_epoch()).count());
	}
}}