/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

#include <unordered_map>
#include <functional>
#include <iostream>
#include "Entity.hpp"

namespace ecs {
	template <typename I, typename T>
	class DataBank {
	public:
		static DataBank<I, T> &get() {
			thread_local static DataBank<I, T> bank;

			return (bank);
		}

		static T &get(I iterator) {
			DataBank<I, T> &bank = DataBank<I,T>::get();
			if (!bank.creator) {
				std::cout << "src/game_engine/ecs/DataBank: creator not initialised" << std::endl;
				exit(84);
			}
			if (bank.map.find(iterator) == bank.map.end())
				bank.map[iterator] = bank.creator(iterator);
			return (bank.map[iterator]);
		}

		static void deleteAt(I iterator) {
			DataBank<I, T> &bank = DataBank<I,T>::get();
			bank.map.erase(iterator);
		}

		T &operator[] (I iterator) {
			if (!creator) {
				std::cout << "src/game_engine/ecs/DataBank: creator not initialised" << std::endl;
				exit(84);
			}
			if (map.find(iterator) == map.end())
				map[iterator] = creator(iterator);
			return (map[iterator]);
		}


		std::function<T(I)>		creator;
		std::unordered_map<I, T>	map;
	};
}