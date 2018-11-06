cmake_minimum_required(VERSION 3.12)
project(CPP_rtype_2018)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(src/game_engine)

add_executable(CPP_rtype_2018
	src/game_engine/ecs/Ecs.hpp
	src/game_engine/ecs/Entity.cpp
	src/game_engine/ecs/Entity.hpp
	src/game_engine/ecs/ListComponent.hpp src/game_engine/core/CoreVector.hpp src/game_engine/component/graphical/AnimatedSprite.hpp src/game_engine/component/graphical/AnimatedSpriteMap.hpp src/game_engine/system/graphical/InitAnimatedSprite.cpp src/game_engine/system/graphical/InitAnimatedSprite.hpp src/game_engine/core/Time.cpp src/game_engine/core/Time.hpp src/game_engine/sfml/Graphic.cpp src/game_engine/sfml/Graphic.hpp src/game_engine/component/control/Keyboard.hpp src/game_engine/component/control/Mouse.hpp src/game_engine/component/control/Controller.hpp src/game_engine/system/control/Controls.hpp src/game_engine/system/control/Controls.cpp)
