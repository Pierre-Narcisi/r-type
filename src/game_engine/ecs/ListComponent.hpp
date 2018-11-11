//
// Created by seble on 01/11/2018.
//

#ifndef ECS_LISTCOMPONENT_HPP
#define ECS_LISTCOMPONENT_HPP

#include <vector>
#include <unordered_map>
#include <functional>
#include "Entity.hpp"

namespace hidden {
    template <typename T>
    class ListComponent {
    public:
        static ListComponent<T> &get() {
            static ListComponent<T> listComponent;

            return listComponent;
        }

        template <typename ...Args>
        std::function<void()> addComponent(ID id, Args... args) {
            _ids.emplace_back(id);
            _component.push_back(T(args...));
            return ([id, this](){
                auto ids = this->_ids.begin();
                auto cpnts = this->_component.begin();
                for (ids, cpnts; *ids != id && ids != _ids.end(); ids++, cpnts++);
                if (ids != _ids.end()) {
			_ids.erase(ids);
			_component.erase(cpnts);
		}
            });
        }

        std::vector<ID> getIdForComponent(std::function<bool(T&)> function) {
        	std::vector<ID> ids;
		auto id = _ids.begin();

        	for (auto component = _component.begin(); component != _component.end(); component++, id++) {
        		if (function(*component))
        			ids.push_back(*id);
        	}
		return ids;
        }

        std::vector<T> &getComponentList() {
            return _component;
        }

        std::vector<ID> &getIdsList() {
            return _ids;
        }

        T &operator[] (ID id) {
        	auto strtId = _ids.begin();
        	auto strsCpnt = _component.begin();
        	for (; strtId != _ids.end() && *strtId != id; strsCpnt++, strtId++);
			if (strtId == _ids.end())
				return *(new T());
        	return *strsCpnt;
        }

    private:
        std::vector<ID> _ids;
        std::vector<T>  _component;
    };
}


#endif //ECS_LISTCOMPONENT_HPP
