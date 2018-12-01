//
// Created by pierre on 20/11/2018.
//

#include "component/graphical/Sprite.hpp"
#include <boost/filesystem.hpp>
#include <chrono>

namespace game {
    struct AnimationRtype {
        AnimationRtype() {}
        AnimationRtype(std::string path, int middle, int frame)
        {
            _framesPerSecond = frame;
            _actualSprite = _middle = middle;
            std::set<std::string> sorted;
			if (boost::filesystem::exists(path)) {
				boost::filesystem::directory_iterator	endItr;
				for (boost::filesystem::directory_iterator itr(path);itr != endItr;++itr) {
					if (boost::filesystem::is_regular(itr->status())) {
						sorted.insert(itr->path().string());
					}
				}
				for (auto it = sorted.begin(); it != sorted.end(); it++) {
					_animation.emplace_back(*it);
				}
			} else {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Missing directory \"" << path << "\"" << std::endl;
				exit(84);
			}

			if (_animation.size() == 0) {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Directory must at least have 1 sprite" << std::endl;
				exit(84);
			}
        }

        int     _framesPerSecond;
        int     _middle;
        int     _actualSprite;

        std::vector<ecs::component::Sprite>		_animation;
        std::chrono::time_point<std::chrono::system_clock>     _lastchange;
    };
}