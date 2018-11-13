cmake_minimum_required(VERSION 3.10)
project(rtype)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/game_engine)

add_executable(rtype

	lib/TimedEvent/TimedEvent.cpp
	lib/TimedEvent/TimedEvent.hpp
	lib/TimedEvent/TimedEventAdmin.cpp
	lib/TimedEvent/TimedEventAdmin.hpp

	src/game_engine/ecs/Ecs.hpp
	src/game_engine/ecs/Entity.cpp
	src/game_engine/ecs/Entity.hpp
	src/game_engine/ecs/ListComponent.hpp
	src/game_engine/core/CoreVector.hpp
	src/game_engine/component/graphical/AnimatedSprite.hpp
	src/game_engine/component/graphical/AnimatedSpriteMap.hpp
	src/game_engine/core/Time.cpp
	src/game_engine/core/Time.hpp
	src/game_engine/sfml/Graphic.cpp
	src/game_engine/sfml/Graphic.hpp
	src/game_engine/component/control/Keyboard.hpp
	src/game_engine/component/control/Mouse.hpp
	src/game_engine/component/control/Controller.hpp
	src/game_engine/system/control/Controls.hpp
	src/game_engine/system/control/Controls.cpp src/Main.cpp
	src/game_engine/component/graphical/Sprite.hpp src/game_engine/system/graphical/Sprites.cpp src/game_engine/system/graphical/Sprites.hpp src/game_engine/component/physic/Position.hpp src/game_engine/component/control/DeplacementKeyBoard.hpp src/game_engine/component/physic/Speed.hpp src/game_engine/component/physic/Acceleration.hpp src/game_engine/system/physic/Speeds.cpp src/game_engine/system/physic/Speeds.hpp src/game_engine/system/physic/Acceleration.cpp src/game_engine/system/physic/Acceleration.hpp src/game_engine/component/physic/Hitbox.hpp)

target_link_libraries(rtype /usr/lib/x86_64-linux-gnu/libsfml-window.so)
target_link_libraries(rtype /usr/lib/x86_64-linux-gnu/libsfml-graphics.so)
target_link_libraries(rtype /usr/lib/x86_64-linux-gnu/libsfml-system.so)
target_link_libraries(rtype /usr/lib/x86_64-linux-gnu/libsfml-audio.so)
target_link_libraries(rtype /usr/lib/x86_64-linux-gnu/libpthread.so)

