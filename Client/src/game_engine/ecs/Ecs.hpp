//
// Created by seble on 01/11/2018.
//

#ifndef ECS_ECS_HPP
#define ECS_ECS_HPP

#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "ListComponent.hpp"

namespace ecs{
    class Ecs {
    public:

        Ecs() {}

        static Ecs &get() {
        	static Ecs ecs;

        	return ecs;
        }

        template <typename T>
        static std::unordered_map<ID, T> &getComponentMap() {
		return hidden::ListComponent<T>::get().getComponentMap();
        }

        template<typename T, typename ...Args>
        static void addComponent(ID id, Args... args){
            get()._deleteIds[id][std::string(typeid(T).name())] = hidden::ListComponent<T>::get().addComponent(id, args...);
        }

        static void deleteId(ID id) {
            for (auto &del : get()._deleteIds[id]) {
            	del.second();
            }
            get()._deleteIds[id].clear();
        }

        template <typename T>
        static void deleteComponentforId(ID id) {
			get()._deleteIds[id][std::string(typeid(T).name())]();
			get()._deleteIds[id].erase(std::string(typeid(T).name()));
        }

        template <typename ...Args>
        static std::vector<ID> filter() {
        	std::vector<ID> valableId;
			for (auto it = get()._deleteIds.begin(); it != get()._deleteIds.end(); ++it)
			{
        		if (idHasComponents<Args...>(it->first))
					valableId.emplace_back(it->first);
			}
		return (valableId);
        }

		template <typename ...Args>
		static bool idHasComponents(ID id) {
		    isIn<Args...> isin;
		    return (isin(id));
		}

		void addUpdate(int priority, std::function<void()> function) {
    	    updates.emplace(priority, function);
    	}

	    void update () {
   	    	for (auto &func : updates) {
   		     	func.second();
        	}
    	}

        std::unordered_map<ID, std::unordered_map<std::string, std::function<void()>>>  _deleteIds;
    private:
        std::multimap<int, std::function<void()>>					updates;

        template <typename ...Ts>
        struct isIn {
        	bool operator() (ID id);
        };

        template <typename T>
	struct isIn<T> {
		bool operator() (ID id) {
			auto &vec = hidden::ListComponent<T>::get().getComponentMap();
			return (vec.find(id) != vec.end());
		}
	};

	template <typename T, typename ...Args>
	struct isIn<T, Args...> {
		bool operator() (ID id) {
			isIn<Args...> isin;
			auto &vec = hidden::ListComponent<T>::get().getComponentMap();
			return ((vec.find(id) != vec.end()) && isin(id));
		}
	};

    };
}


#endif //ECS_ECS_HPP
