cmake_minimum_required(VERSION 3.10)
project(rtype)

set(CMAKE_CXX_STANDARD 17)
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

else ()
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -W -Wall -Wextra -Wno-missing-field-initializers -Wno-unused-parameter")
endif ()


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(Client/src/game_engine)
include_directories(Client/src/game)

set(COMMONS_SRCS
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

	Common/JsonBuilder/JsonBuilder.hpp
	Common/JsonBuilder/JsonBuilder.cpp
)

add_executable(rtype
	${COMMONS_SRCS}

	Client/lib/TimedEvent/TimedEvent.cpp
	Client/lib/TimedEvent/TimedEvent.hpp
	Client/lib/TimedEvent/TimedEventAdmin.cpp
	Client/lib/TimedEvent/TimedEventAdmin.hpp

	Client/src/game/component/ai.hpp
	Client/src/game/enemy/enemy1/enemy1.hpp
	Client/src/game/enemy/enemy1/enemy1.cpp
	Client/src/game/enemy/enemy.hpp

	Client/src/game_engine/ecs/Ecs.hpp
	Client/src/game_engine/ecs/Entity.cpp
	Client/src/game_engine/ecs/Entity.hpp
	Client/src/game_engine/ecs/ListComponent.hpp
	Client/src/game_engine/core/CoreVector.hpp
	Client/src/game_engine/component/graphical/AnimatedSprite.hpp
	Client/src/game_engine/component/graphical/AnimatedSpriteMap.hpp
	Client/src/game_engine/core/Time.cpp
	Client/src/game_engine/core/Time.hpp
	Client/src/game_engine/sfml/Graphic.cpp
	Client/src/game_engine/sfml/Graphic.hpp
	Client/src/game_engine/component/control/Keyboard.hpp
	Client/src/game_engine/component/control/Mouse.hpp
	Client/src/game_engine/component/control/Controller.hpp
	Client/src/game_engine/system/control/Controls.hpp
	Client/src/game_engine/system/control/Controls.cpp Client/src/Main.cpp
	Client/src/game_engine/component/graphical/Sprite.hpp
	Client/src/game_engine/system/graphical/Graphicals.cpp
	Client/src/game_engine/system/graphical/Graphicals.hpp
	Client/src/game_engine/component/physic/Position.hpp
	Client/src/game_engine/component/control/DeplacementKeyBoard.hpp
	Client/src/game_engine/component/physic/Speed.hpp
	Client/src/game_engine/component/physic/Acceleration.hpp
	Client/src/game_engine/system/physic/Speeds.cpp
	Client/src/game_engine/system/physic/Speeds.hpp
	Client/src/game_engine/system/physic/Acceleration.cpp
	Client/src/game_engine/system/physic/Acceleration.hpp
	Client/src/game_engine/component/physic/Hitbox.hpp
	Client/src/game_engine/component/graphical/Drawable.hpp
	Client/src/game_engine/ecs/DataBank.hpp
	Client/src/game_engine/component/audio/Sound.hpp
	Client/src/game_engine/component/control/DeplacementMouse.hpp
)

find_package (Threads)
target_link_libraries(rtype ${CONAN_LIBS})
target_link_libraries(rtype ${CMAKE_THREAD_LIBS_INIT})


project(server)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Server)
include_directories(Server/includes)
include_directories(Common)

add_executable(server
	${COMMONS_SRCS}

	Server/src/Main.cpp

	Server/includes/Server.hpp
	Server/src/Server.cpp

	Server/includes/ClientConnection.hpp
	Server/src/ClientConnection.cpp

	Server/includes/TcpListener.hpp
	Server/includes/TcpListenerSlave.hpp
	Server/includes/TcpListener.tpp
)