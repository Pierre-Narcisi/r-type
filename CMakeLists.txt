cmake_minimum_required(VERSION 3.10)
project(rtype)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/game_engine)

add_executable(rtype
	src/game_engine/ecs/Ecs.hpp
	src/game_engine/ecs/Entity.cpp
	src/game_engine/ecs/Entity.hpp
	src/game_engine/ecs/ListComponent.hpp
	src/game_engine/core/CoreVector.hpp
	src/game_engine/component/graphical/AnimatedSprite.hpp
	src/game_engine/component/graphical/AnimatedSpriteMap.hpp
	src/game_engine/system/graphical/InitAnimatedSprite.cpp
	src/game_engine/system/graphical/InitAnimatedSprite.hpp
	src/game_engine/core/Time.cpp
	src/game_engine/core/Time.hpp
	src/game_engine/sfml/Graphic.cpp
	src/game_engine/sfml/Graphic.hpp
	src/game_engine/component/control/Keyboard.hpp
	src/game_engine/component/control/Mouse.hpp
	src/game_engine/component/control/Controller.hpp
	src/game_engine/system/control/Controls.hpp
	src/game_engine/system/control/Controls.cpp src/Main.cpp src/game_engine/component/graphical/Sprite.hpp)

target_link_libraries(rtype /usr/lib/x86_64-linux-gnu/libsfml-window.so)
target_link_libraries(rtype /usr/lib/x86_64-linux-gnu/libsfml-graphics.so)
target_link_libraries(rtype /usr/lib/x86_64-linux-gnu/libsfml-system.so)
target_link_libraries(rtype /usr/lib/x86_64-linux-gnu/libsfml-audio.so)


project(Server)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Server)
include_directories(Server/includes)
include_directories(Common)

add_executable(Server
	Common/WindowsCtor.cpp

	Common/TcpSocket/ATcpSocket.hpp
	Common/TcpSocket/TcpSocket.hpp
	Common/TcpSocket/CommonTcpSocket.cpp
	Common/TcpSocket/Unix/UnixTcpSocket.cpp
	Common/TcpSocket/Unix/UnixTcpSocket.hpp
	Common/TcpSocket/Windows/WindowsTcpSocket.cpp
	Common/TcpSocket/Windows/WindowsTcpSocket.hpp

	Common/Opts/Opts.cpp
	Common/Opts/Opts.hpp

	Common/Json/includes/Entity.hpp
	Common/Json/includes/Parser.hpp
	Common/Json/src/Entity.cpp
	Common/Json/src/Parser.cpp

	Server/src/Main.cpp

	Server/includes/Server.hpp
	Server/src/Server.cpp

	Server/includes/ClientConnection.hpp
	Server/src/ClientConnection.cpp

	Server/includes/TcpListener.hpp
	Server/src/TcpListener.cpp
)